# Swagger API Documentation Guide

## Обзор

В ваше Spring Boot приложение успешно добавлена документация API с помощью Swagger/OpenAPI 3. Это позволяет автоматически генерировать интерактивную документацию для вашего REST API.

## Доступ к Swagger UI

После запуска приложения Swagger UI будет доступен по следующим адресам:

- **Swagger UI**: http://localhost:8080/swagger-ui.html
- **OpenAPI JSON**: http://localhost:8080/v3/api-docs
- **OpenAPI YAML**: http://localhost:8080/v3/api-docs.yaml

## Как использовать

### 1. Запуск приложения

```bash
mvn spring-boot:run
```

### 2. Открытие Swagger UI

Перейдите в браузере по адресу: http://localhost:8080/swagger-ui.html

### 3. Тестирование API

#### Регистрация нового пользователя:
1. Найдите раздел "Authentication"
2. Откройте endpoint `POST /api/auth/register`
3. Нажмите "Try it out"
4. Введите JSON:
```json
{
  "username": "testuser",
  "password": "password123"
}
```
5. Нажмите "Execute"

#### Аутентификация:
1. Откройте endpoint `POST /api/auth/login`
2. Введите те же учетные данные
3. Скопируйте полученный JWT токен из ответа

#### Использование защищенных endpoint'ов:
1. Нажмите кнопку "Authorize" в верхней части страницы
2. В поле "Value" введите: `Bearer YOUR_JWT_TOKEN_HERE`
3. Нажмите "Authorize"
4. Теперь можете тестировать защищенные endpoint'ы в разделе "User Management"

## Структура API

### Authentication (Аутентификация)
- `POST /api/auth/register` - Регистрация нового пользователя
- `POST /api/auth/login` - Вход в систему

### User Management (Управление пользователями)
- `GET /api/users/profile` - Получить профиль текущего пользователя
- `GET /api/users/admin` - Данные для администратора (требует роль ADMIN)

## Настройки безопасности

Swagger UI настроен для работы с JWT аутентификацией:
- Все endpoint'ы в `/api/auth/**` доступны без аутентификации
- Остальные endpoint'ы требуют JWT токен в заголовке Authorization
- Swagger UI страницы исключены из системы безопасности

## Конфигурационные файлы

### Основная конфигурация: `SwaggerConfig.java`
- Настройка OpenAPI документации
- Конфигурация JWT безопасности
- Информация о API (title, description, version)

### Настройки в `application.properties`:
```properties
# Swagger/OpenAPI Configuration
springdoc.api-docs.path=/v3/api-docs
springdoc.swagger-ui.path=/swagger-ui.html
springdoc.swagger-ui.enabled=true
springdoc.packages-to-scan=com.example.demo.controllers
springdoc.show-actuator=false
```

### Обновления безопасности в `SecurityConfig.java`:
Добавлены исключения для Swagger endpoint'ов:
```java
.requestMatchers("/swagger-ui/**", "/v3/api-docs/**", "/swagger-ui.html").permitAll()
```

## Аннотации Swagger в коде

### Контроллеры:
- `@Tag` - группировка endpoint'ов
- `@Operation` - описание операции
- `@ApiResponses` - возможные ответы
- `@SecurityRequirement` - требования безопасности

### DTO классы:
- `@Schema` - описание модели данных
- Примеры значений и валидация

## Дополнительные возможности

- Автоматическая генерация клиентского кода
- Экспорт OpenAPI спецификации
- Интеграция с системами мониторинга API
- Возможность кастомизации UI темы

## Полезные ссылки

- [SpringDoc OpenAPI Documentation](https://springdoc.org/)
- [OpenAPI 3 Specification](https://spec.openapis.org/oas/v3.0.3/)
- [Swagger UI Documentation](https://swagger.io/tools/swagger-ui/) 