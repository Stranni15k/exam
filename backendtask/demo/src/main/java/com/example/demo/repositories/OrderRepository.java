package com.example.demo.repositories;

import com.example.demo.models.Order;
import com.example.demo.models.User;
import com.example.demo.models.OrderStatus;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;
import java.util.List;

@Repository
public interface OrderRepository extends JpaRepository<Order, Long> {

    List<Order> findByUser(User user);
    
    List<Order> findByUserOrderByIdDesc(User user);
    
    @Query("SELECT o FROM Order o JOIN FETCH o.orderItems oi JOIN FETCH oi.product WHERE o.user = :user")
    List<Order> findByUserWithItemsAndProducts(@Param("user") User user);
    
    @Query("SELECT o FROM Order o JOIN FETCH o.orderItems oi JOIN FETCH oi.product JOIN FETCH o.user")
    List<Order> findAllWithItemsAndProducts();
} 