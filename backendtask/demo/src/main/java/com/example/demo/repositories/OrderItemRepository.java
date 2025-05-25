package com.example.demo.repositories;

import com.example.demo.models.OrderItem;
import com.example.demo.models.Order;
import com.example.demo.models.Product;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;
import java.util.List;

@Repository
public interface OrderItemRepository extends JpaRepository<OrderItem, Long> {

    List<OrderItem> findByOrder(Order order);
    
    List<OrderItem> findByProduct(Product product);
    
    @Query("SELECT oi.product.id, oi.product.name, oi.product.price, SUM(oi.quantity), SUM(oi.quantity * oi.product.price) " +
           "FROM OrderItem oi " +
           "GROUP BY oi.product.id, oi.product.name, oi.product.price " +
           "ORDER BY SUM(oi.quantity) DESC")
    List<Object[]> findTopSellingProducts();
}