package com.example.demo.services;

import com.example.demo.dto.CategoryDto;
import com.example.demo.models.Category;
import com.example.demo.repositories.CategoryRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
@Transactional
public class CategoryService {

    @Autowired
    private CategoryRepository categoryRepository;

    public List<CategoryDto> getAllCategories() {
        return categoryRepository.findAll().stream()
                .map(this::convertToDto)
                .collect(Collectors.toList());
    }

    public Optional<CategoryDto> getCategoryById(Long id) {
        return categoryRepository.findById(id)
                .map(this::convertToDto);
    }

    public CategoryDto createCategory(CategoryDto categoryDto) {
        Category category = new Category();
        category.setName(categoryDto.getName());
        Category savedCategory = categoryRepository.save(category);
        return convertToDto(savedCategory);
    }

    public Optional<CategoryDto> updateCategory(Long id, CategoryDto categoryDto) {
        return categoryRepository.findById(id)
                .map(category -> {
                    category.setName(categoryDto.getName());
                    Category savedCategory = categoryRepository.save(category);
                    return convertToDto(savedCategory);
                });
    }

    public boolean deleteCategory(Long id) {
        if (categoryRepository.existsById(id)) {
            categoryRepository.deleteById(id);
            return true;
        }
        return false;
    }

    private CategoryDto convertToDto(Category category) {
        return new CategoryDto(
                category.getId(),
                category.getName()
        );
    }
} 