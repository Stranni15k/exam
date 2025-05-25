package com.example.demo.utils;

import com.example.demo.models.Role;
import com.example.demo.models.User;
import com.example.demo.repositories.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;

@Component
public class AuthUtils {

    @Autowired
    private UserRepository userRepository;

    public User getCurrentUser() {
        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        
        if (authentication == null || !authentication.isAuthenticated()) {
            throw new RuntimeException("User not authenticated");
        }
        
        String username = authentication.getName();
        return userRepository.findByUsername(username)
                .orElseThrow(() -> new RuntimeException("User not found"));
    }


    public boolean isCurrentUserAdmin() {
        try {
            User currentUser = getCurrentUser();
            return currentUser.getRole() == Role.ADMIN;
        } catch (RuntimeException e) {
            return false;
        }
    }

    public boolean canAccessUserData(Long userId) {
        if (isCurrentUserAdmin()) {
            return true;
        }
        
        try {
            User currentUser = getCurrentUser();
            return currentUser.getId().equals(userId);
        } catch (RuntimeException e) {
            return false;
        }
    }

    public boolean canAccessProfile(Long profileId) {
        if (isCurrentUserAdmin()) {
            return true;
        }
        
        try {
            User currentUser = getCurrentUser();
            return currentUser.getProfile() != null &&
                   currentUser.getProfile().getId().equals(profileId);
        } catch (RuntimeException e) {
            return false;
        }
    }


    public boolean canAccessProfileByUserId(Long userId) {
        return canAccessUserData(userId);
    }

    public boolean canAccessOrder(Long orderId) {
        if (isCurrentUserAdmin()) {
            return true;
        }
        
        return false;
    }

    public void requireUserDataAccess(Long userId) {
        if (!canAccessUserData(userId)) {
            throw new RuntimeException("Access denied: You can only access your own data");
        }
    }

    public void requireProfileAccess(Long profileId) {
        if (!canAccessProfile(profileId)) {
            throw new RuntimeException("Access denied: You can only access your own profile");
        }
    }

    public void requireProfileAccessByUserId(Long userId) {
        if (!canAccessProfileByUserId(userId)) {
            throw new RuntimeException("Access denied: You can only access your own profile");
        }
    }

    public void requireAdminAccess() {
        if (!isCurrentUserAdmin()) {
            throw new RuntimeException("Access denied: Admin privileges required");
        }
    }
} 