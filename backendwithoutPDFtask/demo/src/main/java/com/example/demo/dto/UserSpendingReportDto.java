package com.example.demo.dto;

import java.math.BigDecimal;
import java.util.List;

public class UserSpendingReportDto {
    private String username;
    private Long userId;
    private List<OrderReportDto> orders;
    private BigDecimal totalSpent;
    
    public UserSpendingReportDto() {}
    
    public UserSpendingReportDto(String username, Long userId, List<OrderReportDto> orders, BigDecimal totalSpent) {
        this.username = username;
        this.userId = userId;
        this.orders = orders;
        this.totalSpent = totalSpent;
    }
    
    public String getUsername() {
        return username;
    }
    
    public void setUsername(String username) {
        this.username = username;
    }
    
    public Long getUserId() {
        return userId;
    }
    
    public void setUserId(Long userId) {
        this.userId = userId;
    }
    
    public List<OrderReportDto> getOrders() {
        return orders;
    }
    
    public void setOrders(List<OrderReportDto> orders) {
        this.orders = orders;
    }
    
    public BigDecimal getTotalSpent() {
        return totalSpent;
    }
    
    public void setTotalSpent(BigDecimal totalSpent) {
        this.totalSpent = totalSpent;
    }
} 