package com.example.demo.services;

import com.example.demo.dto.OrderDto;
import com.example.demo.dto.OrderCreateDto;
import com.example.demo.dto.OrderItemRequestDto;
import com.example.demo.dto.OrderWithItemsCreateDto;
import com.example.demo.dto.OrderWithItemsDto;
import com.example.demo.models.Order;
import com.example.demo.models.OrderItem;
import com.example.demo.models.User;
import com.example.demo.models.Product;
import com.example.demo.repositories.OrderRepository;
import com.example.demo.repositories.UserRepository;
import com.example.demo.repositories.ProductRepository;
import com.example.demo.utils.AuthUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;

@Service
@Transactional
public class OrderService {

    @Autowired
    private OrderRepository orderRepository;

    @Autowired
    private UserRepository userRepository;

    @Autowired
    private ProductRepository productRepository;
    
    @Autowired
    private AuthUtils authUtils;

    public List<OrderDto> getAllOrders() {
        // Только администраторы могут получить все заказы
        authUtils.requireAdminAccess();
        
        return orderRepository.findAll().stream()
                .map(this::convertToDto)
                .collect(Collectors.toList());
    }

    public Optional<OrderDto> getOrderById(Long id) {
        // Проверяем доступ к заказу
        if (!authUtils.isCurrentUserAdmin() && !isOrderOwner(id, authUtils.getCurrentUser().getUsername())) {
            throw new RuntimeException("Access denied: You can only access your own orders");
        }
        
        return orderRepository.findById(id)
                .map(this::convertToDto);
    }

    public OrderDto createOrder(OrderCreateDto orderCreateDto) {
        // Проверяем, может ли пользователь создать заказ для указанного userId
        authUtils.requireUserDataAccess(orderCreateDto.getUserId());
        
        User user = userRepository.findById(orderCreateDto.getUserId())
                .orElseThrow(() -> new RuntimeException("User not found"));

        Order order = new Order();
        order.setUser(user);
        order.setStatus(orderCreateDto.getStatus());
        
        Order savedOrder = orderRepository.save(order);
        return convertToDto(savedOrder);
    }

    public Optional<OrderDto> updateOrder(Long id, OrderCreateDto orderCreateDto) {
        // Проверяем доступ к заказу
        if (!authUtils.isCurrentUserAdmin() && !isOrderOwner(id, authUtils.getCurrentUser().getUsername())) {
            throw new RuntimeException("Access denied: You can only modify your own orders");
        }
        
        // Проверяем, может ли пользователь назначить заказ указанному userId
        authUtils.requireUserDataAccess(orderCreateDto.getUserId());
        
        return orderRepository.findById(id)
                .map(order -> {
                    User user = userRepository.findById(orderCreateDto.getUserId())
                            .orElseThrow(() -> new RuntimeException("User not found"));
                    
                    order.setUser(user);
                    order.setStatus(orderCreateDto.getStatus());
                    
                    Order savedOrder = orderRepository.save(order);
                    return convertToDto(savedOrder);
                });
    }

    public boolean deleteOrder(Long id) {
        // Проверяем доступ к заказу
        if (!authUtils.isCurrentUserAdmin() && !isOrderOwner(id, authUtils.getCurrentUser().getUsername())) {
            throw new RuntimeException("Access denied: You can only delete your own orders");
        }
        
        if (orderRepository.existsById(id)) {
            orderRepository.deleteById(id);
            return true;
        }
        return false;
    }

    public OrderDto createOrderWithItems(OrderWithItemsCreateDto orderWithItemsCreateDto) {
        // Проверяем, может ли пользователь создать заказ для указанного userId
        authUtils.requireUserDataAccess(orderWithItemsCreateDto.getUserId());
        
        User user = userRepository.findById(orderWithItemsCreateDto.getUserId())
                .orElseThrow(() -> new RuntimeException("User not found"));

        Order order = new Order();
        order.setUser(user);
        order.setStatus(orderWithItemsCreateDto.getStatus());
        
        // Сначала сохраняем заказ
        Order savedOrder = orderRepository.save(order);
        
        // Затем добавляем товары в заказ
        if (orderWithItemsCreateDto.getItems() != null && !orderWithItemsCreateDto.getItems().isEmpty()) {
            for (OrderItemRequestDto itemDto : orderWithItemsCreateDto.getItems()) {
                Product product = productRepository.findById(itemDto.getProductId())
                        .orElseThrow(() -> new RuntimeException("Product not found with id: " + itemDto.getProductId()));
                
                OrderItem orderItem = new OrderItem();
                orderItem.setOrder(savedOrder);
                orderItem.setProduct(product);
                orderItem.setQuantity(itemDto.getQuantity());
                
                savedOrder.getOrderItems().add(orderItem);
            }
            
            // Сохраняем заказ с добавленными товарами
            savedOrder = orderRepository.save(savedOrder);
        }
        
        return convertToDto(savedOrder);
    }

    public Optional<OrderWithItemsDto> getOrderWithItemsById(Long id) {
        // Проверяем доступ к заказу
        if (!authUtils.isCurrentUserAdmin() && !isOrderOwner(id, authUtils.getCurrentUser().getUsername())) {
            throw new RuntimeException("Access denied: You can only access your own orders");
        }
        
        return orderRepository.findById(id)
                .map(this::convertToDetailDto);
    }

    private OrderDto convertToDto(Order order) {
        Set<Long> orderItemIds = order.getOrderItems().stream()
                .map(OrderItem::getId)
                .collect(Collectors.toSet());
        
        return new OrderDto(
                order.getId(),
                order.getStatus(),
                order.getUser().getId(),
                orderItemIds
        );
    }

    private OrderWithItemsDto convertToDetailDto(Order order) {
        List<OrderWithItemsDto.OrderItemDetailDto> itemDetails = order.getOrderItems().stream()
                .map(orderItem -> new OrderWithItemsDto.OrderItemDetailDto(
                        orderItem.getId(),
                        orderItem.getQuantity(),
                        orderItem.getProduct().getId(),
                        orderItem.getProduct().getName()
                ))
                .collect(Collectors.toList());
        
        return new OrderWithItemsDto(
                order.getId(),
                order.getStatus(),
                order.getUser().getId(),
                itemDetails
        );
    }

    /**
     * Проверяет, является ли пользователь владельцем заказа
     */
    public boolean isOrderOwner(Long orderId, String username) {
        return orderRepository.findById(orderId)
                .map(order -> order.getUser().getUsername().equals(username))
                .orElse(false);
    }

    /**
     * Получает заказы текущего пользователя
     */
    public List<OrderDto> getOrdersByCurrentUser() {
        // Получаем текущего аутентифицированного пользователя
        User currentUser = authUtils.getCurrentUser();
        
        return orderRepository.findByUser(currentUser).stream()
                .map(this::convertToDto)
                .collect(Collectors.toList());
    }
} 