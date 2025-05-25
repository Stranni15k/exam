package com.example.demo.dto;

import com.example.demo.models.OrderStatus;
import java.util.List;

import jakarta.validation.Valid;
import jakarta.validation.constraints.NotEmpty;
import jakarta.validation.constraints.NotNull;

public class OrderWithItemsCreateDto {

    @NotNull(message = "Order status is required")
    private OrderStatus status;

    @NotNull(message = "User ID is required")
    private Long userId;

    @NotEmpty(message = "Order must contain at least one item")
    @Valid
    private List<@Valid OrderItemRequestDto> items;

    public OrderWithItemsCreateDto() {}

    public OrderWithItemsCreateDto(OrderStatus status, Long userId, List<OrderItemRequestDto> items) {
        this.status = status;
        this.userId = userId;
        this.items = items;
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

    public List<OrderItemRequestDto> getItems() {
        return items;
    }

    public void setItems(List<OrderItemRequestDto> items) {
        this.items = items;
    }
} 