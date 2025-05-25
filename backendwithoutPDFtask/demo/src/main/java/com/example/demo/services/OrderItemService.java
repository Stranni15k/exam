package com.example.demo.services;

import com.example.demo.dto.OrderItemDto;
import com.example.demo.dto.OrderItemCreateDto;
import com.example.demo.models.Order;
import com.example.demo.models.OrderItem;
import com.example.demo.models.Product;
import com.example.demo.repositories.OrderItemRepository;
import com.example.demo.repositories.OrderRepository;
import com.example.demo.repositories.ProductRepository;
import com.example.demo.utils.AuthUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
@Transactional
public class OrderItemService {

    @Autowired
    private OrderItemRepository orderItemRepository;

    @Autowired
    private OrderRepository orderRepository;

    @Autowired
    private ProductRepository productRepository;
    
    @Autowired
    private AuthUtils authUtils;

    public List<OrderItemDto> getAllOrderItems() {
        // Только администраторы могут получить все элементы заказов
        authUtils.requireAdminAccess();
        
        return orderItemRepository.findAll().stream()
                .map(this::convertToDto)
                .collect(Collectors.toList());
    }

    public Optional<OrderItemDto> getOrderItemById(Long id) {
        // Проверяем доступ к элементу заказа
        if (!authUtils.isCurrentUserAdmin() && !isOrderItemOwner(id, authUtils.getCurrentUser().getUsername())) {
            throw new RuntimeException("Access denied: You can only access your own order items");
        }
        
        return orderItemRepository.findById(id)
                .map(this::convertToDto);
    }

    public OrderItemDto createOrderItem(OrderItemCreateDto orderItemCreateDto) {
        Order order = orderRepository.findById(orderItemCreateDto.getOrderId())
                .orElseThrow(() -> new RuntimeException("Order not found"));
        
        // Проверяем, может ли пользователь добавлять элементы в этот заказ
        if (!authUtils.isCurrentUserAdmin() && !order.getUser().getUsername().equals(authUtils.getCurrentUser().getUsername())) {
            throw new RuntimeException("Access denied: You can only add items to your own orders");
        }
        
        Product product = productRepository.findById(orderItemCreateDto.getProductId())
                .orElseThrow(() -> new RuntimeException("Product not found"));

        OrderItem orderItem = new OrderItem();
        orderItem.setOrder(order);
        orderItem.setProduct(product);
        orderItem.setQuantity(orderItemCreateDto.getQuantity());
        
        OrderItem savedOrderItem = orderItemRepository.save(orderItem);
        return convertToDto(savedOrderItem);
    }

    public Optional<OrderItemDto> updateOrderItem(Long id, OrderItemCreateDto orderItemCreateDto) {
        // Проверяем доступ к элементу заказа
        if (!authUtils.isCurrentUserAdmin() && !isOrderItemOwner(id, authUtils.getCurrentUser().getUsername())) {
            throw new RuntimeException("Access denied: You can only modify your own order items");
        }
        
        return orderItemRepository.findById(id)
                .map(orderItem -> {
                    Order order = orderRepository.findById(orderItemCreateDto.getOrderId())
                            .orElseThrow(() -> new RuntimeException("Order not found"));
                    
                    // Проверяем, может ли пользователь переместить элемент в этот заказ
                    if (!authUtils.isCurrentUserAdmin() && !order.getUser().getUsername().equals(authUtils.getCurrentUser().getUsername())) {
                        throw new RuntimeException("Access denied: You can only move items to your own orders");
                    }
                    
                    Product product = productRepository.findById(orderItemCreateDto.getProductId())
                            .orElseThrow(() -> new RuntimeException("Product not found"));
                    
                    orderItem.setOrder(order);
                    orderItem.setProduct(product);
                    orderItem.setQuantity(orderItemCreateDto.getQuantity());
                    
                    OrderItem savedOrderItem = orderItemRepository.save(orderItem);
                    return convertToDto(savedOrderItem);
                });
    }

    public boolean deleteOrderItem(Long id) {
        // Проверяем доступ к элементу заказа
        if (!authUtils.isCurrentUserAdmin() && !isOrderItemOwner(id, authUtils.getCurrentUser().getUsername())) {
            throw new RuntimeException("Access denied: You can only delete your own order items");
        }
        
        if (orderItemRepository.existsById(id)) {
            orderItemRepository.deleteById(id);
            return true;
        }
        return false;
    }

    private OrderItemDto convertToDto(OrderItem orderItem) {
        return new OrderItemDto(
                orderItem.getId(),
                orderItem.getQuantity(),
                orderItem.getOrder().getId(),
                orderItem.getProduct().getId()
        );
    }

    /**
     * Проверяет, является ли пользователь владельцем элемента заказа
     */
    public boolean isOrderItemOwner(Long orderItemId, String username) {
        return orderItemRepository.findById(orderItemId)
                .map(orderItem -> orderItem.getOrder().getUser().getUsername().equals(username))
                .orElse(false);
    }
} 