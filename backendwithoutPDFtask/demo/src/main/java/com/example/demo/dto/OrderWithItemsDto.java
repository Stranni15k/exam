package com.example.demo.dto;

import com.example.demo.models.OrderStatus;
import java.util.List;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.NotEmpty;
import jakarta.validation.Valid;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;

public class OrderWithItemsDto {
    private Long id;
    
    @NotNull(message = "Order status is required")
    private OrderStatus status;
    
    @NotNull(message = "User ID is required")
    private Long userId;
    
    @NotEmpty(message = "Order must have at least one item")
    @Valid
    private List<OrderItemDetailDto> items;

    public OrderWithItemsDto() {}

    public OrderWithItemsDto(Long id, OrderStatus status, Long userId, List<OrderItemDetailDto> items) {
        this.id = id;
        this.status = status;
        this.userId = userId;
        this.items = items;
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

    public List<OrderItemDetailDto> getItems() {
        return items;
    }

    public void setItems(List<OrderItemDetailDto> items) {
        this.items = items;
    }

    public static class OrderItemDetailDto {
        private Long id;
        
        @NotNull(message = "Quantity is required")
        @Min(value = 1, message = "Quantity must be at least 1")
        private Integer quantity;
        
        @NotNull(message = "Product ID is required")
        private Long productId;
        
        @NotBlank(message = "Product name is required")
        private String productName;

        public OrderItemDetailDto() {}

        public OrderItemDetailDto(Long id, Integer quantity, Long productId, String productName) {
            this.id = id;
            this.quantity = quantity;
            this.productId = productId;
            this.productName = productName;
        }

        public Long getId() {
            return id;
        }

        public void setId(Long id) {
            this.id = id;
        }

        public Integer getQuantity() {
            return quantity;
        }

        public void setQuantity(Integer quantity) {
            this.quantity = quantity;
        }

        public Long getProductId() {
            return productId;
        }

        public void setProductId(Long productId) {
            this.productId = productId;
        }

        public String getProductName() {
            return productName;
        }

        public void setProductName(String productName) {
            this.productName = productName;
        }

    }
} 