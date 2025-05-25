package com.example.demo.services;

import com.example.demo.dto.UserDto;
import com.example.demo.dto.UserCreateDto;
import com.example.demo.models.User;
import com.example.demo.repositories.UserRepository;
import com.example.demo.utils.AuthUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
@Transactional
public class UserService {

    @Autowired
    private UserRepository userRepository;

    @Autowired
    private PasswordEncoder passwordEncoder;
    
    @Autowired
    private AuthUtils authUtils;

    public List<UserDto> getAllUsers() {
        authUtils.requireAdminAccess();
        
        return userRepository.findAll().stream()
                .map(this::convertToDto)
                .collect(Collectors.toList());
    }

    public Optional<UserDto> getUserById(Long id) {
        authUtils.requireUserDataAccess(id);
        
        return userRepository.findById(id)
                .map(this::convertToDto);
    }
    
    public Optional<UserDto> getByUsername(String username) {
        return userRepository.findByUsername(username)
                .map(this::convertToDto);
    }

    public UserDto createUser(UserCreateDto userCreateDto) {
        User user = new User();
        user.setUsername(userCreateDto.getUsername());
        user.setPassword(passwordEncoder.encode(userCreateDto.getPassword()));
        user.setRole(userCreateDto.getRole());
        
        User savedUser = userRepository.save(user);
        return convertToDto(savedUser);
    }

    public Optional<UserDto> updateUser(Long id, UserCreateDto userCreateDto) {
        // Проверяем доступ к данным пользователя
        authUtils.requireUserDataAccess(id);
        
        return userRepository.findById(id)
                .map(user -> {
                    user.setUsername(userCreateDto.getUsername());
                    if (userCreateDto.getPassword() != null && !userCreateDto.getPassword().isEmpty()) {
                        user.setPassword(passwordEncoder.encode(userCreateDto.getPassword()));
                    }
                    user.setRole(userCreateDto.getRole());
                    
                    User savedUser = userRepository.save(user);
                    return convertToDto(savedUser);
                });
    }

    public boolean deleteUser(Long id) {
        // Проверяем доступ к данным пользователя
        authUtils.requireUserDataAccess(id);
        
        if (userRepository.existsById(id)) {
            userRepository.deleteById(id);
            return true;
        }
        return false;
    }

    private UserDto convertToDto(User user) {
        return new UserDto(
                user.getId(),
                user.getUsername(),
                user.getRole()
        );
    }
} 