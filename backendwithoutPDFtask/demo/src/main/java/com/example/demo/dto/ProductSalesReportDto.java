package com.example.demo.dto;

import java.math.BigDecimal;

public class ProductSalesReportDto {
    private Long productId;
    private String productName;
    private BigDecimal unitPrice;
    private Integer totalQuantitySold;
    private BigDecimal totalRevenue;
    
    public ProductSalesReportDto() {}
    
    public ProductSalesReportDto(Long productId, String productName, BigDecimal unitPrice, 
                                Integer totalQuantitySold, BigDecimal totalRevenue) {
        this.productId = productId;
        this.productName = productName;
        this.unitPrice = unitPrice;
        this.totalQuantitySold = totalQuantitySold;
        this.totalRevenue = totalRevenue;
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
    
    public BigDecimal getUnitPrice() {
        return unitPrice;
    }
    
    public void setUnitPrice(BigDecimal unitPrice) {
        this.unitPrice = unitPrice;
    }
    
    public Integer getTotalQuantitySold() {
        return totalQuantitySold;
    }
    
    public void setTotalQuantitySold(Integer totalQuantitySold) {
        this.totalQuantitySold = totalQuantitySold;
    }
    
    public BigDecimal getTotalRevenue() {
        return totalRevenue;
    }
    
    public void setTotalRevenue(BigDecimal totalRevenue) {
        this.totalRevenue = totalRevenue;
    }
} 