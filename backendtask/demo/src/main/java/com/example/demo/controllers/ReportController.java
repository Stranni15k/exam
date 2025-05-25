package com.example.demo.controllers;

import com.example.demo.dto.SpendingReportDto;
import com.example.demo.dto.TopProductsReportDto;
import com.example.demo.services.PdfReportService;
import com.example.demo.services.ReportService;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.Parameter;
import io.swagger.v3.oas.annotations.responses.ApiResponse;
import io.swagger.v3.oas.annotations.responses.ApiResponses;
import io.swagger.v3.oas.annotations.tags.Tag;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

@RestController
@RequestMapping("/api/reports")
@Tag(name = "Reports", description = "API для работы с отчетами")
public class ReportController {

    @Autowired
    private ReportService reportService;

    @Autowired
    private PdfReportService pdfReportService;

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

    @GetMapping("/spending/pdf")
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<byte[]> downloadSpendingReportPdf() {
        try {
            SpendingReportDto report = reportService.generateSpendingReport();
            byte[] pdfBytes = pdfReportService.generateSpendingReportPdf(report);
            
            String filename = "spending_report_" + 
                LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss")) + ".pdf";
            
            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.APPLICATION_PDF);
            headers.setContentDispositionFormData("attachment", filename);
            headers.setContentLength(pdfBytes.length);
            
            return new ResponseEntity<>(pdfBytes, headers, HttpStatus.OK);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/spending/user/{userId}/pdf")
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<byte[]> downloadUserSpendingReportPdf(
            @Parameter(description = "ID пользователя", required = true)
            @PathVariable Long userId) {
        try {
            SpendingReportDto report = reportService.generateUserSpendingReport(userId);
            byte[] pdfBytes = pdfReportService.generateSpendingReportPdf(report);
            
            String filename = "user_" + userId + "_spending_report_" + 
                LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss")) + ".pdf";
            
            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.APPLICATION_PDF);
            headers.setContentDispositionFormData("attachment", filename);
            headers.setContentLength(pdfBytes.length);
            
            return new ResponseEntity<>(pdfBytes, headers, HttpStatus.OK);
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

    @GetMapping("/top-products/pdf")
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<byte[]> downloadTopProductsReportPdf() {
        try {
            TopProductsReportDto report = reportService.generateTopProductsReport();
            byte[] pdfBytes = pdfReportService.generateTopProductsReportPdf(report);
            
            String filename = "top_products_report_" + 
                LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss")) + ".pdf";
            
            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.APPLICATION_PDF);
            headers.setContentDispositionFormData("attachment", filename);
            headers.setContentLength(pdfBytes.length);
            
            return new ResponseEntity<>(pdfBytes, headers, HttpStatus.OK);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
} 