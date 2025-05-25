package com.example.demo.services;

import com.example.demo.dto.ProductDto;
import com.example.demo.models.Category;
import com.example.demo.models.Product;
import com.example.demo.repositories.CategoryRepository;
import com.example.demo.repositories.ProductRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.HashSet;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;

@Service
@Transactional
public class ProductService {

    @Autowired
    private ProductRepository productRepository;

    @Autowired
    private CategoryRepository categoryRepository;

    public List<ProductDto> getAllProducts() {
        return productRepository.findAll().stream()
                .map(this::convertToDto)
                .collect(Collectors.toList());
    }

    public Optional<ProductDto> getProductById(Long id) {
        return productRepository.findById(id)
                .map(this::convertToDto);
    }

    public ProductDto createProduct(ProductDto productDto) {
        Product product = new Product();
        product.setName(productDto.getName());
        product.setPrice(productDto.getPrice());
        
        if (productDto.getCategoryIds() != null && !productDto.getCategoryIds().isEmpty()) {
            Set<Category> categories = new HashSet<>(categoryRepository.findAllById(productDto.getCategoryIds()));
            product.setCategories(categories);
        }
        
        Product savedProduct = productRepository.save(product);
        return convertToDto(savedProduct);
    }

    public Optional<ProductDto> updateProduct(Long id, ProductDto productDto) {
        return productRepository.findById(id)
                .map(product -> {
                    product.setName(productDto.getName());
                    product.setPrice(productDto.getPrice());
                    
                    // Обновляем категории
                    if (productDto.getCategoryIds() != null) {
                        Set<Category> categories = new HashSet<>(categoryRepository.findAllById(productDto.getCategoryIds()));
                        product.setCategories(categories);
                    }
                    
                    Product savedProduct = productRepository.save(product);
                    return convertToDto(savedProduct);
                });
    }

    public boolean deleteProduct(Long id) {
        if (productRepository.existsById(id)) {
            productRepository.deleteById(id);
            return true;
        }
        return false;
    }

    private ProductDto convertToDto(Product product) {
        Set<Long> categoryIds = product.getCategories().stream()
                .map(Category::getId)
                .collect(Collectors.toSet());
        
        return new ProductDto(
                product.getId(),
                product.getName(),
                product.getPrice(),
                categoryIds
        );
    }
} 