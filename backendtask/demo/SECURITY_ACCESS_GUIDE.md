# Руководство по разграничению доступа к эндпоинтам

## Обзор системы безопасности

Приложение использует Spring Security с JWT аутентификацией и ролевой моделью доступа. Система поддерживает две роли:
- **USER** - обычный пользователь
- **ADMIN** - администратор

## Принципы разграничения доступа

### 1. Публичные эндпоинты (без аутентификации)
- `POST /api/auth/register` - Регистрация
- `POST /api/auth/login` - Вход в систему
- Swagger UI эндпоинты

### 2. Эндпоинты только для чтения (доступны всем аутентифицированным)
- `GET /api/products` - Просмотр всех товаров
- `GET /api/products/{id}` - Просмотр конкретного товара
- `GET /api/categories` - Просмотр всех категорий
- `GET /api/categories/{id}` - Просмотр конкретной категории

### 3. Эндпоинты только для администраторов
- **Управление пользователями:**
  - `GET /api/users` - Просмотр всех пользователей
  - `GET /api/users/{id}` - Просмотр конкретного пользователя
  - `POST /api/users` - Создание пользователя
  - `PUT /api/users/{id}` - Обновление пользователя
  - `DELETE /api/users/{id}` - Удаление пользователя

- **Управление товарами:**
  - `POST /api/products` - Создание товара
  - `PUT /api/products/{id}` - Обновление товара
  - `DELETE /api/products/{id}` - Удаление товара

- **Управление категориями:**
  - `POST /api/categories` - Создание категории
  - `PUT /api/categories/{id}` - Обновление категории
  - `DELETE /api/categories/{id}` - Удаление категории

- **Просмотр всех данных:**
  - `GET /api/orders` - Просмотр всех заказов
  - `GET /api/order-items` - Просмотр всех элементов заказов
  - `GET /api/profiles` - Просмотр всех профилей пользователей

### 4. Эндпоинты с владением ресурсами
Пользователи могут работать только со своими ресурсами, админы - со всеми.

#### Заказы:
- `GET /api/orders/{id}` - Админ или владелец заказа
- `PUT /api/orders/{id}` - Админ или владелец заказа
- `DELETE /api/orders/{id}` - Админ или владелец заказа
- `GET /api/orders/{id}/details` - Админ или владелец заказа
- `GET /api/orders/my-orders` - Только аутентифицированные (свои заказы)
- `POST /api/orders` - Любой аутентифицированный пользователь
- `POST /api/orders/with-items` - Любой аутентифицированный пользователь

#### Элементы заказов:
- `GET /api/order-items/{id}` - Админ или владелец элемента заказа
- `PUT /api/order-items/{id}` - Админ или владелец элемента заказа
- `DELETE /api/order-items/{id}` - Админ или владелец элемента заказа
- `POST /api/order-items` - Любой аутентифицированный пользователь

#### Профили пользователей:
- `GET /api/profiles/{id}` - Админ или владелец профиля
- `GET /api/profiles/user/{userId}` - Админ или владелец профиля
- `PUT /api/profiles/{id}` - Админ или владелец профиля
- `DELETE /api/profiles/{id}` - Админ или владелец профиля
- `POST /api/profiles` - Любой аутентифицированный пользователь

## Аннотации безопасности

### @PreAuthorize аннотации используемые в проекте:

1. **`@PreAuthorize("hasRole('ADMIN')")`** - Только администраторы
2. **`@PreAuthorize("isAuthenticated()")`** - Любой аутентифицированный пользователь
3. **`@PreAuthorize("hasRole('ADMIN') or @serviceName.isOwner(#id, authentication.name)")`** - Админ или владелец ресурса

### Методы проверки владения:

#### OrderService:
```java
public boolean isOrderOwner(Long orderId, String username)
```

#### OrderItemService:
```java
public boolean isOrderItemOwner(Long orderItemId, String username)
```

#### UserProfileService:
```java
public boolean isProfileOwner(Long profileId, String username)
public boolean isProfileOwnerByUserId(Long userId, String username)
```

## Настройка в SecurityConfig

```java
@Configuration
@EnableWebSecurity
@EnableMethodSecurity  // Включает поддержку @PreAuthorize
public class SecurityConfig {
    // ... конфигурация
}
```

## Примеры использования

### Вход как администратор:
```bash
curl -X POST http://localhost:8080/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"username": "admin", "password": "admin"}'
```

### Создание товара (только админ):
```bash
curl -X POST http://localhost:8080/api/products \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_JWT_TOKEN" \
  -d '{"name": "New Product", "price": 99.99}'
```

### Просмотр своих заказов:
```bash
curl -X GET http://localhost:8080/api/orders/my-orders \
  -H "Authorization: Bearer YOUR_JWT_TOKEN"
```

## Обработка ошибок доступа

При нарушении правил доступа возвращается:
- **403 Forbidden** - Недостаточно прав
- **401 Unauthorized** - Не аутентифицирован

## Рекомендации по безопасности

1. Всегда проверяйте JWT токен в заголовке Authorization
2. Используйте HTTPS в продакшене
3. Регулярно обновляйте JWT секретный ключ
4. Логируйте попытки несанкционированного доступа
5. Реализуйте rate limiting для предотвращения атак 