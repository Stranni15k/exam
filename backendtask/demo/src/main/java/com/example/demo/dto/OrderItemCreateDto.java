package com.example.demo.dto;

import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Min;

public class OrderItemCreateDto {
    @NotNull(message = "Quantity is required")
    @Min(value = 1, message = "Quantity must be at least 1")
    private Integer quantity;
    
    @NotNull(message = "Order ID is required")
    private Long orderId;
    
    @NotNull(message = "Product ID is required")
    private Long productId;

    public OrderItemCreateDto() {}

    public OrderItemCreateDto(Integer quantity, Long orderId, Long productId) {
        this.quantity = quantity;
        this.orderId = orderId;
        this.productId = productId;
    }

    public Integer getQuantity() {
        return quantity;
    }

    public void setQuantity(Integer quantity) {
        this.quantity = quantity;
    }

    public Long getOrderId() {
        return orderId;
    }

    public void setOrderId(Long orderId) {
        this.orderId = orderId;
    }

    public Long getProductId() {
        return productId;
    }

    public void setProductId(Long productId) {
        this.productId = productId;
    }
} 