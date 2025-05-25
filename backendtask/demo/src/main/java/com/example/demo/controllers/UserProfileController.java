package com.example.demo.controllers;

import com.example.demo.dto.CreateUserProfileDto;
import com.example.demo.dto.UpdateUserProfileDto;
import com.example.demo.dto.UserProfileDto;
import com.example.demo.services.UserProfileService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;
import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/api/profiles")
@Validated
public class UserProfileController {
    
    private final UserProfileService userProfileService;
    
    @Autowired
    public UserProfileController(UserProfileService userProfileService) {
        this.userProfileService = userProfileService;
    }
    
    @PostMapping
    public ResponseEntity<?> createProfile(@Valid @RequestBody CreateUserProfileDto createDto) {
        try {
            UserProfileDto createdProfile = userProfileService.createProfile(createDto);
            return ResponseEntity.status(HttpStatus.CREATED).body(createdProfile);
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST)
                    .body("Error creating profile: " + e.getMessage());
        }
    }
    
    @GetMapping("/{id}")
    public ResponseEntity<?> getProfileById(@PathVariable Long id) {
        try {
            Optional<UserProfileDto> profile = userProfileService.getProfileById(id);
            if (profile.isPresent()) {
                return ResponseEntity.ok(profile.get());
            } else {
                return ResponseEntity.status(HttpStatus.NOT_FOUND)
                        .body("Profile not found with id: " + id);
            }
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.FORBIDDEN)
                    .body(e.getMessage());
        }
    }
    
    @GetMapping("/user/{userId}")
    public ResponseEntity<?> getProfileByUserId(@PathVariable Long userId) {
        try {
            Optional<UserProfileDto> profile = userProfileService.getProfileByUserId(userId);
            if (profile.isPresent()) {
                return ResponseEntity.ok(profile.get());
            } else {
                return ResponseEntity.status(HttpStatus.NOT_FOUND)
                        .body("Profile not found for user with id: " + userId);
            }
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.FORBIDDEN)
                    .body(e.getMessage());
        }
    }
    
    @GetMapping
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<List<UserProfileDto>> getAllProfiles() {
        List<UserProfileDto> profiles = userProfileService.getAllProfiles();
        return ResponseEntity.ok(profiles);
    }
    
    @PutMapping("/{id}")
    public ResponseEntity<?> updateProfile(@PathVariable Long id,
                                         @Valid @RequestBody UpdateUserProfileDto updateDto) {
        try {
            UserProfileDto updatedProfile = userProfileService.updateProfile(id, updateDto);
            return ResponseEntity.ok(updatedProfile);
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST)
                    .body("Error updating profile: " + e.getMessage());
        }
    }
    
    @DeleteMapping("/{id}")
    public ResponseEntity<?> deleteProfile(@PathVariable Long id) {
        try {
            userProfileService.deleteProfile(id);
            return ResponseEntity.ok("Profile deleted successfully");
        } catch (RuntimeException e) {
            return ResponseEntity.status(HttpStatus.NOT_FOUND)
                    .body("Error deleting profile: " + e.getMessage());
        }
    }
} 