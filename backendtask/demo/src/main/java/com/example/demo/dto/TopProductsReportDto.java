package com.example.demo.dto;

import java.time.LocalDateTime;
import java.util.List;

public class TopProductsReportDto {
    private LocalDateTime reportDate;
    private List<ProductSalesReportDto> topProducts;
    private Integer totalProductsAnalyzed;
    
    public TopProductsReportDto() {}
    
    public TopProductsReportDto(LocalDateTime reportDate, List<ProductSalesReportDto> topProducts, 
                               Integer totalProductsAnalyzed) {
        this.reportDate = reportDate;
        this.topProducts = topProducts;
        this.totalProductsAnalyzed = totalProductsAnalyzed;
    }
    
    public LocalDateTime getReportDate() {
        return reportDate;
    }
    
    public void setReportDate(LocalDateTime reportDate) {
        this.reportDate = reportDate;
    }
    
    public List<ProductSalesReportDto> getTopProducts() {
        return topProducts;
    }
    
    public void setTopProducts(List<ProductSalesReportDto> topProducts) {
        this.topProducts = topProducts;
    }
    
    public Integer getTotalProductsAnalyzed() {
        return totalProductsAnalyzed;
    }
    
    public void setTotalProductsAnalyzed(Integer totalProductsAnalyzed) {
        this.totalProductsAnalyzed = totalProductsAnalyzed;
    }
} 