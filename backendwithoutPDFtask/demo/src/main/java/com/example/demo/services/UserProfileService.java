package com.example.demo.services;

import com.example.demo.dto.CreateUserProfileDto;
import com.example.demo.dto.UpdateUserProfileDto;
import com.example.demo.dto.UserProfileDto;
import com.example.demo.models.User;
import com.example.demo.models.UserProfile;
import com.example.demo.repositories.UserProfileRepository;
import com.example.demo.repositories.UserRepository;
import com.example.demo.utils.AuthUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
@Transactional
public class UserProfileService {
    
    private final UserProfileRepository userProfileRepository;
    private final UserRepository userRepository;

    
    @Autowired
    private AuthUtils authUtils;
    
    @Autowired
    public UserProfileService(UserProfileRepository userProfileRepository, UserRepository userRepository) {
        this.userProfileRepository = userProfileRepository;
        this.userRepository = userRepository;
    }
    
    public UserProfileDto createProfile(CreateUserProfileDto createDto) {
        authUtils.requireProfileAccessByUserId(createDto.getUserId());

        User user = userRepository.findById(createDto.getUserId())
                .orElseThrow(() -> new RuntimeException("User not found with id: " + createDto.getUserId()));
        
        if (userProfileRepository.existsByUserId(createDto.getUserId())) {
            throw new RuntimeException("Profile already exists for user with id: " + createDto.getUserId());
        }
        
        if (userProfileRepository.existsByEmail(createDto.getEmail())) {
            throw new RuntimeException("Profile with this email already exists: " + createDto.getEmail());
        }
        
        UserProfile profile = new UserProfile();
        profile.setUser(user);
        profile.setFirstName(createDto.getFirstName());
        profile.setLastName(createDto.getLastName());
        profile.setEmail(createDto.getEmail());
        profile.setAddress(createDto.getAddress());
        
        UserProfile savedProfile = userProfileRepository.save(profile);
        return convertToDto(savedProfile);
    }
    
    @Transactional(readOnly = true)
    public Optional<UserProfileDto> getProfileById(Long id) {
        authUtils.requireProfileAccess(id);
        
        return userProfileRepository.findById(id)
                .map(this::convertToDto);
    }
    
    @Transactional(readOnly = true)
    public Optional<UserProfileDto> getProfileByUserId(Long userId) {
        authUtils.requireProfileAccessByUserId(userId);
        
        return userProfileRepository.findByUserId(userId)
                .map(this::convertToDto);
    }
    
    @Transactional(readOnly = true)
    public List<UserProfileDto> getAllProfiles() {
        authUtils.requireAdminAccess();
        
        return userProfileRepository.findAll().stream()
                .map(this::convertToDto)
                .collect(Collectors.toList());
    }
    
    public UserProfileDto updateProfile(Long id, UpdateUserProfileDto updateDto) {
        authUtils.requireProfileAccess(id);
        
        UserProfile profile = userProfileRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Profile not found with id: " + id));
        
        if (updateDto.getEmail() != null && !updateDto.getEmail().equals(profile.getEmail())) {
            if (userProfileRepository.existsByEmail(updateDto.getEmail())) {
                throw new RuntimeException("Profile with this email already exists: " + updateDto.getEmail());
            }
        }
        
        if (updateDto.getFirstName() != null) {
            profile.setFirstName(updateDto.getFirstName());
        }
        if (updateDto.getLastName() != null) {
            profile.setLastName(updateDto.getLastName());
        }
        if (updateDto.getEmail() != null) {
            profile.setEmail(updateDto.getEmail());
        }
        if (updateDto.getAddress() != null) {
            profile.setAddress(updateDto.getAddress());
        }
        
        UserProfile updatedProfile = userProfileRepository.save(profile);
        return convertToDto(updatedProfile);
    }
    
    public void deleteProfile(Long id) {
        authUtils.requireProfileAccess(id);
        
        if (!userProfileRepository.existsById(id)) {
            throw new RuntimeException("Profile not found with id: " + id);
        }
        UserProfile userProfile = userProfileRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("User profile not found"));

        User user = userRepository.findById(userProfile.getUser().getId())
                .orElseThrow(() -> new RuntimeException("User not found"));

        user.setProfile(null);
        userRepository.save(user);
        userProfileRepository.deleteById(id);
    }
    
    private UserProfileDto convertToDto(UserProfile profile) {
        return new UserProfileDto(
                profile.getId(),
                profile.getFirstName(),
                profile.getLastName(),
                profile.getEmail(),
                profile.getAddress(),
                profile.getUser().getId(),
                profile.getUser().getUsername()
        );
    }
} 