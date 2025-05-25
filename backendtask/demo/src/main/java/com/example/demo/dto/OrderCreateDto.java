package com.example.demo.dto;

import com.example.demo.models.OrderStatus;
import jakarta.validation.constraints.NotNull;

public class OrderCreateDto {
    @NotNull(message = "Order status is required")
    private OrderStatus status;
    
    @NotNull(message = "User ID is required")
    private Long userId;

    public OrderCreateDto() {}

    public OrderCreateDto(OrderStatus status, Long userId) {
        this.status = status;
        this.userId = userId;
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
} 