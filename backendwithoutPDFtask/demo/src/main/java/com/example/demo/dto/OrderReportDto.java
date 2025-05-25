package com.example.demo.dto;

import java.math.BigDecimal;

public class OrderReportDto {
    private Long orderId;
    private String orderStatus;
    private BigDecimal totalAmount;
    
    public OrderReportDto() {}
    
    public OrderReportDto(Long orderId, String orderStatus, BigDecimal totalAmount) {
        this.orderId = orderId;
        this.orderStatus = orderStatus;
        this.totalAmount = totalAmount;
    }
    
    public Long getOrderId() {
        return orderId;
    }
    
    public void setOrderId(Long orderId) {
        this.orderId = orderId;
    }
    
    public String getOrderStatus() {
        return orderStatus;
    }
    
    public void setOrderStatus(String orderStatus) {
        this.orderStatus = orderStatus;
    }
    
    public BigDecimal getTotalAmount() {
        return totalAmount;
    }
    
    public void setTotalAmount(BigDecimal totalAmount) {
        this.totalAmount = totalAmount;
    }
} 