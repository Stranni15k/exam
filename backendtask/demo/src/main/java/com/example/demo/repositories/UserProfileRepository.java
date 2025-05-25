package com.example.demo.repositories;

import com.example.demo.models.UserProfile;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import java.util.Optional;

@Repository
public interface UserProfileRepository extends JpaRepository<UserProfile, Long> {
    
    Optional<UserProfile> findByUserId(Long userId);
    
    boolean existsByUserId(Long userId);
    
    Optional<UserProfile> findByEmail(String email);
    
    boolean existsByEmail(String email);
} 