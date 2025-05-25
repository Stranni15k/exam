package com.example.demo.config;

import com.example.demo.dto.UserCreateDto;
import com.example.demo.models.Role;
import com.example.demo.services.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Component;

@Component
public class DataInitializer implements CommandLineRunner {

    @Autowired
    private UserService userService;

    @Autowired
    private PasswordEncoder passwordEncoder;

    @Override
    public void run(String... args) throws Exception {
        initializeAdmin();
    }

    private void initializeAdmin() {
        String adminUsername = "admin";
        String adminPassword = "admin";

        if (!userService.getByUsername(adminUsername).isPresent()) {
            UserCreateDto admin = new UserCreateDto();
            admin.setUsername(adminUsername);
            admin.setPassword(adminPassword);
            admin.setRole(Role.ADMIN);
            userService.createUser(admin);

            System.out.println("Администратор создан:");
            System.out.println("Логин: " + adminUsername);
            System.out.println("Пароль: " + adminPassword);
        } else {
            System.out.println("Администратор уже существует");
        }
    }
} 