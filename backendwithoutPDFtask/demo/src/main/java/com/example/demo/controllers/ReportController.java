package com.example.demo.controllers;

import com.example.demo.dto.SpendingReportDto;
import com.example.demo.dto.TopProductsReportDto;
import com.example.demo.services.ReportService;

import io.swagger.v3.oas.annotations.Parameter;
import io.swagger.v3.oas.annotations.tags.Tag;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/reports")
@Tag(name = "Reports", description = "API для работы с отчетами")
public class ReportController {

    @Autowired
    private ReportService reportService;

    @GetMapping("/spending")
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<SpendingReportDto> getSpendingReport() {
        try {
            SpendingReportDto report = reportService.generateSpendingReport();
            return ResponseEntity.ok(report);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/spending/user/{userId}")
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<SpendingReportDto> getUserSpendingReport(
            @Parameter(description = "ID пользователя", required = true)
            @PathVariable Long userId) {
        try {
            SpendingReportDto report = reportService.generateUserSpendingReport(userId);
            return ResponseEntity.ok(report);
        } catch (RuntimeException e) {
            return ResponseEntity.notFound().build();
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/top-products")
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<TopProductsReportDto> getTopProductsReport() {
        try {
            TopProductsReportDto report = reportService.generateTopProductsReport();
            return ResponseEntity.ok(report);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
} 