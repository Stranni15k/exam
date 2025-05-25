package com.example.demo.dto;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.List;

public class SpendingReportDto {
    private LocalDateTime reportDate;
    private List<UserSpendingReportDto> userReports;
    private BigDecimal grandTotal;
    
    public SpendingReportDto() {}
    
    public SpendingReportDto(LocalDateTime reportDate, List<UserSpendingReportDto> userReports, BigDecimal grandTotal) {
        this.reportDate = reportDate;
        this.userReports = userReports;
        this.grandTotal = grandTotal;
    }
    
    public LocalDateTime getReportDate() {
        return reportDate;
    }
    
    public void setReportDate(LocalDateTime reportDate) {
        this.reportDate = reportDate;
    }
    
    public List<UserSpendingReportDto> getUserReports() {
        return userReports;
    }
    
    public void setUserReports(List<UserSpendingReportDto> userReports) {
        this.userReports = userReports;
    }
    
    public BigDecimal getGrandTotal() {
        return grandTotal;
    }
    
    public void setGrandTotal(BigDecimal grandTotal) {
        this.grandTotal = grandTotal;
    }
} 