package com.example.demo.services;

import com.example.demo.dto.*;
import com.example.demo.models.Order;
import com.example.demo.models.OrderItem;
import com.example.demo.models.User;
import com.example.demo.repositories.OrderRepository;
import com.example.demo.repositories.OrderItemRepository;
import com.example.demo.repositories.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@Service
public class ReportService {

    @Autowired
    private OrderRepository orderRepository;

    @Autowired
    private OrderItemRepository orderItemRepository;

    @Autowired
    private UserRepository userRepository;

    public SpendingReportDto generateSpendingReport() {
        // Получаем всех пользователей
        List<User> allUsers = userRepository.findAll();
        
        // Получаем все заказы с товарами
        List<Order> allOrders = orderRepository.findAllWithItemsAndProducts();
        
        // Группируем заказы по пользователям
        Map<User, List<Order>> ordersByUser = allOrders.stream()
                .collect(Collectors.groupingBy(Order::getUser));
        
        List<UserSpendingReportDto> userReports = new ArrayList<>();
        BigDecimal grandTotal = BigDecimal.ZERO;
        
        // Проходим по всем пользователям
        for (User user : allUsers) {
            List<Order> userOrders = ordersByUser.getOrDefault(user, new ArrayList<>());
            
            List<OrderReportDto> orderReports = new ArrayList<>();
            BigDecimal userTotal = BigDecimal.ZERO;
            
            // Если у пользователя есть заказы, обрабатываем их
            for (Order order : userOrders) {
                BigDecimal orderTotal = BigDecimal.ZERO;
                
                for (OrderItem item : order.getOrderItems()) {
                    BigDecimal itemTotal = item.getProduct().getPrice()
                            .multiply(BigDecimal.valueOf(item.getQuantity()));
                    orderTotal = orderTotal.add(itemTotal);
                }
                
                OrderReportDto orderReport = new OrderReportDto(
                        order.getId(),
                        order.getStatus().toString(),
                        orderTotal
                );
                
                orderReports.add(orderReport);
                userTotal = userTotal.add(orderTotal);
            }
            
            // Создаем отчет для пользователя (даже если у него нет заказов)
            UserSpendingReportDto userReport = new UserSpendingReportDto(
                    user.getUsername(),
                    user.getId(),
                    orderReports,
                    userTotal
            );
            
            userReports.add(userReport);
            grandTotal = grandTotal.add(userTotal);
        }
        
        return new SpendingReportDto(LocalDateTime.now(), userReports, grandTotal);
    }
    
    public SpendingReportDto generateUserSpendingReport(Long userId) {
        User user = userRepository.findById(userId)
                .orElseThrow(() -> new RuntimeException("User not found"));
        
        List<Order> userOrders = orderRepository.findByUserWithItemsAndProducts(user);
        
        List<OrderReportDto> orderReports = new ArrayList<>();
        BigDecimal userTotal = BigDecimal.ZERO;
        
        for (Order order : userOrders) {
            BigDecimal orderTotal = BigDecimal.ZERO;
            
            for (OrderItem item : order.getOrderItems()) {
                BigDecimal itemTotal = item.getProduct().getPrice()
                        .multiply(BigDecimal.valueOf(item.getQuantity()));
                orderTotal = orderTotal.add(itemTotal);
            }
            
            OrderReportDto orderReport = new OrderReportDto(
                    order.getId(),
                    order.getStatus().toString(),
                    orderTotal
            );
            
            orderReports.add(orderReport);
            userTotal = userTotal.add(orderTotal);
        }
        
        UserSpendingReportDto userReport = new UserSpendingReportDto(
                user.getUsername(),
                user.getId(),
                orderReports,
                userTotal
        );
        
        List<UserSpendingReportDto> userReports = List.of(userReport);
        
        return new SpendingReportDto(LocalDateTime.now(), userReports, userTotal);
    }
    
    public TopProductsReportDto generateTopProductsReport() {
        List<Object[]> salesData = orderItemRepository.findTopSellingProducts();
        
        List<ProductSalesReportDto> topProducts = new ArrayList<>();
        
        // Ограничиваем до топ-10
        int limit = Math.min(10, salesData.size());
        
        for (int i = 0; i < limit; i++) {
            Object[] row = salesData.get(i);
            
            Long productId = (Long) row[0];
            String productName = (String) row[1];
            BigDecimal unitPrice = (BigDecimal) row[2];
            Long totalQuantitySoldLong = (Long) row[3];
            BigDecimal totalRevenue = (BigDecimal) row[4];
            
            Integer totalQuantitySold = totalQuantitySoldLong.intValue();
            
            ProductSalesReportDto productReport = new ProductSalesReportDto(
                    productId,
                    productName,
                    unitPrice,
                    totalQuantitySold,
                    totalRevenue
            );
            
            topProducts.add(productReport);
        }
        
        return new TopProductsReportDto(LocalDateTime.now(), topProducts, salesData.size());
    }
} 