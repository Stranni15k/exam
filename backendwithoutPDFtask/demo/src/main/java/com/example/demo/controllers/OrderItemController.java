package com.example.demo.controllers;

import com.example.demo.dto.OrderItemDto;
import com.example.demo.dto.OrderItemCreateDto;
import com.example.demo.services.OrderItemService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;

import java.util.List;

import jakarta.validation.Valid;

@RestController
@RequestMapping("/api/order-items")
public class OrderItemController {

    private OrderItemService orderItemService;
    @Autowired
    public OrderItemController(OrderItemService orderItemService) {
        this.orderItemService = orderItemService;
    }

    @GetMapping
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<List<OrderItemDto>> getAllOrderItems() {
        List<OrderItemDto> orderItems = orderItemService.getAllOrderItems();
        return ResponseEntity.ok(orderItems);
    }

    @GetMapping("/{id}")
    public ResponseEntity<?> getOrderItemById(@Valid @PathVariable Long id) {
        try {
            return orderItemService.getOrderItemById(id)
                    .map(orderItem -> ResponseEntity.ok(orderItem))
                    .orElse(ResponseEntity.notFound().build());
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.FORBIDDEN)
                    .body(e.getMessage());
        }
    }

    @PostMapping
    public ResponseEntity<?> createOrderItem(@Valid @RequestBody OrderItemCreateDto orderItemCreateDto) {
        try {
            OrderItemDto createdOrderItem = orderItemService.createOrderItem(orderItemCreateDto);
            return ResponseEntity.status(HttpStatus.CREATED).body(createdOrderItem);
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST)
                    .body("Error creating order item: " + e.getMessage());
        }
    }

    @PutMapping("/{id}")
    public ResponseEntity<?> updateOrderItem(@PathVariable Long id, @Valid @RequestBody OrderItemCreateDto orderItemCreateDto) {
        try {
            return orderItemService.updateOrderItem(id, orderItemCreateDto)
                    .map(orderItem -> ResponseEntity.ok(orderItem))
                    .orElse(ResponseEntity.notFound().build());
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.FORBIDDEN)
                    .body(e.getMessage());
        }
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<?> deleteOrderItem(@PathVariable Long id) {
        try {
            if (orderItemService.deleteOrderItem(id)) {
                return ResponseEntity.ok().build();
            } else {
                return ResponseEntity.notFound().build();
            }
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.FORBIDDEN)
                    .body(e.getMessage());
        }
    }
} 