package com.example.demo.dto;

import com.example.demo.models.OrderStatus;
import java.util.Set;
import jakarta.validation.constraints.NotNull;

public class OrderDto {
    private Long id;
    
    @NotNull(message = "Order status is required")
    private OrderStatus status;
    
    @NotNull(message = "User ID is required")
    private Long userId;
    
    private Set<Long> orderItemIds;

    public OrderDto() {}

    public OrderDto(Long id, OrderStatus status, Long userId, Set<Long> orderItemIds) {
        this.id = id;
        this.status = status;
        this.userId = userId;
        this.orderItemIds = orderItemIds;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public OrderStatus getStatus() {
        return status;
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }

    public Long getUserId() {
        return userId;
    }

    public void setUserId(Long userId) {
        this.userId = userId;
    }

    public Set<Long> getOrderItemIds() {
        return orderItemIds;
    }

    public void setOrderItemIds(Set<Long> orderItemIds) {
        this.orderItemIds = orderItemIds;
    }
} 