# REST API Документация

## Обзор
Данное API предоставляет CRUD операции для следующих сущностей:
- Categories (Категории)
- Products (Товары)
- Users (Пользователи)
- Orders (Заказы)
- Order Items (Элементы заказа)

## Базовый URL
```
http://localhost:8080/api
```

## Endpoints

### Categories API

#### GET /api/categories
Получить все категории
- **Response**: `List<CategoryDto>`

#### GET /api/categories/{id}
Получить категорию по ID
- **Path Variable**: `id` (Long)
- **Response**: `CategoryDto` | 404 Not Found

#### POST /api/categories
Создать новую категорию
- **Request Body**: `CategoryDto`
- **Response**: `CategoryDto` (201 Created)

#### PUT /api/categories/{id}
Обновить категорию
- **Path Variable**: `id` (Long)
- **Request Body**: `CategoryDto`
- **Response**: `CategoryDto` | 404 Not Found

#### DELETE /api/categories/{id}
Удалить категорию
- **Path Variable**: `id` (Long)
- **Response**: 204 No Content | 404 Not Found

### Products API

#### GET /api/products
Получить все товары
- **Response**: `List<ProductDto>`

#### GET /api/products/{id}
Получить товар по ID
- **Path Variable**: `id` (Long)
- **Response**: `ProductDto` | 404 Not Found

#### POST /api/products
Создать новый товар
- **Request Body**: `ProductDto`
- **Response**: `ProductDto` (201 Created)

#### PUT /api/products/{id}
Обновить товар
- **Path Variable**: `id` (Long)
- **Request Body**: `ProductDto`
- **Response**: `ProductDto` | 404 Not Found

#### DELETE /api/products/{id}
Удалить товар
- **Path Variable**: `id` (Long)
- **Response**: 204 No Content | 404 Not Found

### Users API

#### GET /api/users
Получить всех пользователей
- **Response**: `List<UserDto>`

#### GET /api/users/{id}
Получить пользователя по ID
- **Path Variable**: `id` (Long)
- **Response**: `UserDto` | 404 Not Found

#### POST /api/users
Создать нового пользователя
- **Request Body**: `UserCreateDto`
- **Response**: `UserDto` (201 Created)

#### PUT /api/users/{id}
Обновить пользователя
- **Path Variable**: `id` (Long)
- **Request Body**: `UserCreateDto`
- **Response**: `UserDto` | 404 Not Found

#### DELETE /api/users/{id}
Удалить пользователя
- **Path Variable**: `id` (Long)
- **Response**: 204 No Content | 404 Not Found

### Orders API

#### GET /api/orders
Получить все заказы
- **Response**: `List<OrderDto>`

#### GET /api/orders/{id}
Получить заказ по ID
- **Path Variable**: `id` (Long)
- **Response**: `OrderDto` | 404 Not Found

#### POST /api/orders
Создать новый заказ
- **Request Body**: `OrderCreateDto`
- **Response**: `OrderDto` (201 Created)

#### PUT /api/orders/{id}
Обновить заказ
- **Path Variable**: `id` (Long)
- **Request Body**: `OrderCreateDto`
- **Response**: `OrderDto` | 404 Not Found

#### DELETE /api/orders/{id}
Удалить заказ
- **Path Variable**: `id` (Long)
- **Response**: 204 No Content | 404 Not Found

### Order Items API

#### GET /api/order-items
Получить все элементы заказов
- **Response**: `List<OrderItemDto>`

#### GET /api/order-items/{id}
Получить элемент заказа по ID
- **Path Variable**: `id` (Long)
- **Response**: `OrderItemDto` | 404 Not Found

#### POST /api/order-items
Создать новый элемент заказа
- **Request Body**: `OrderItemCreateDto`
- **Response**: `OrderItemDto` (201 Created)

#### PUT /api/order-items/{id}
Обновить элемент заказа
- **Path Variable**: `id` (Long)
- **Request Body**: `OrderItemCreateDto`
- **Response**: `OrderItemDto` | 404 Not Found

#### DELETE /api/order-items/{id}
Удалить элемент заказа
- **Path Variable**: `id` (Long)
- **Response**: 204 No Content | 404 Not Found

## DTO Структуры

### CategoryDto
```json
{
  "id": 1,
  "name": "Electronics",
  "version": 0
}
```

### ProductDto
```json
{
  "id": 1,
  "name": "Laptop",
  "price": 999.99,
  "version": 0,
  "categoryIds": [1, 2]
}
```

### UserDto (Response)
```json
{
  "id": 1,
  "username": "john_doe",
  "role": "USER",
  "version": 0
}
```

### UserCreateDto (Request)
```json
{
  "username": "john_doe",
  "password": "password123",
  "role": "USER"
}
```

### OrderDto
```json
{
  "id": 1,
  "status": "PENDING",
  "userId": 1,
  "version": 0,
  "orderItemIds": [1, 2]
}
```

### OrderCreateDto
```json
{
  "status": "PENDING",
  "userId": 1
}
```

### OrderItemDto
```json
{
  "id": 1,
  "quantity": 2,
  "orderId": 1,
  "productId": 1,
  "version": 0
}
```

### OrderItemCreateDto
```json
{
  "quantity": 2,
  "orderId": 1,
  "productId": 1
}
```

## Enum Values

### Role
- `USER`
- `ADMIN`

### OrderStatus
- `PENDING`
- `CONFIRMED`
- `SHIPPED`
- `DELIVERED`
- `CANCELLED`

## Примеры запросов

### Создание категории
```bash
curl -X POST http://localhost:8080/api/categories \
  -H "Content-Type: application/json" \
  -d '{"name": "Electronics"}'
```

### Создание товара
```bash
curl -X POST http://localhost:8080/api/products \
  -H "Content-Type: application/json" \
  -d '{"name": "Laptop", "price": 999.99, "categoryIds": [1]}'
```

### Создание пользователя
```bash
curl -X POST http://localhost:8080/api/users \
  -H "Content-Type: application/json" \
  -d '{"username": "john_doe", "password": "password123", "role": "USER"}'
```

### Создание заказа
```bash
curl -X POST http://localhost:8080/api/orders \
  -H "Content-Type: application/json" \
  -d '{"status": "PENDING", "userId": 1}'
```

### Создание элемента заказа
```bash
curl -X POST http://localhost:8080/api/order-items \
  -H "Content-Type: application/json" \
  -d '{"quantity": 2, "orderId": 1, "productId": 1}'
```

## Reports API

### GET /api/reports/spending
Получить отчет о тратах всех пользователей (только для ADMIN)
- **Response**: `SpendingReportDto`
- **Authorization**: Bearer Token (ADMIN role required)

### GET /api/reports/spending/user/{userId}
Получить отчет о тратах конкретного пользователя
- **Path Variable**: `userId` (Long)
- **Response**: `SpendingReportDto` | 404 Not Found
- **Authorization**: Bearer Token (ADMIN role или собственный userId)

### GET /api/reports/spending/pdf
Скачать отчет о тратах всех пользователей в PDF (только для ADMIN)
- **Response**: PDF файл
- **Authorization**: Bearer Token (ADMIN role required)

### GET /api/reports/spending/user/{userId}/pdf
Скачать отчет о тратах конкретного пользователя в PDF
- **Path Variable**: `userId` (Long)
- **Response**: PDF файл | 404 Not Found
- **Authorization**: Bearer Token (ADMIN role или собственный userId)

### GET /api/reports/top-products
Получить отчет топ-10 самых продаваемых товаров (только для ADMIN)
- **Response**: `TopProductsReportDto`
- **Authorization**: Bearer Token (ADMIN role required)

### GET /api/reports/top-products/pdf
Скачать отчет топ-10 товаров в PDF (только для ADMIN)
- **Response**: PDF файл
- **Authorization**: Bearer Token (ADMIN role required)

## Report DTO Структуры

### SpendingReportDto
```json
{
  "reportDate": "2024-01-15T10:30:00",
  "userReports": [
    {
      "username": "john_doe",
      "userId": 1,
      "totalSpent": 1299.98,
      "orders": [
        {
          "orderId": 1,
          "orderStatus": "DELIVERED",
          "totalAmount": 999.99
        },
        {
          "orderId": 2,
          "orderStatus": "PENDING",
          "totalAmount": 299.99
        }
      ]
    },
    {
      "username": "jane_smith",
      "userId": 2,
      "totalSpent": 0,
      "orders": []
    }
  ],
  "grandTotal": 1299.98
}
```

### UserSpendingReportDto
```json
{
  "username": "john_doe",
  "userId": 1,
  "totalSpent": 1299.98,
  "orders": [
    {
      "orderId": 1,
      "orderStatus": "DELIVERED",
      "totalAmount": 999.99
    },
    {
      "orderId": 2,
      "orderStatus": "PENDING",
      "totalAmount": 299.99
    }
  ]
}
```

### OrderReportDto
```json
{
  "orderId": 1,
  "orderStatus": "DELIVERED",
  "totalAmount": 999.99
}
```

### TopProductsReportDto
```json
{
  "reportDate": "2024-01-15T10:30:00",
  "topProducts": [
    {
      "productId": 1,
      "productName": "Laptop",
      "unitPrice": 999.99,
      "totalQuantitySold": 25,
      "totalRevenue": 24999.75
    },
    {
      "productId": 2,
      "productName": "Mouse",
      "unitPrice": 29.99,
      "totalQuantitySold": 15,
      "totalRevenue": 449.85
    }
  ],
  "totalProductsAnalyzed": 50
}
```

### ProductSalesReportDto
```json
{
  "productId": 1,
  "productName": "Laptop",
  "unitPrice": 999.99,
  "totalQuantitySold": 25,
  "totalRevenue": 24999.75
}
```

## Примеры запросов для отчетов

### Получение отчета о тратах всех пользователей
```bash
curl -X GET http://localhost:8080/api/reports/spending \
  -H "Authorization: Bearer YOUR_ADMIN_TOKEN"
```

### Получение отчета о тратах конкретного пользователя
```bash
curl -X GET http://localhost:8080/api/reports/spending/user/1 \
  -H "Authorization: Bearer YOUR_TOKEN"
```

### Скачивание PDF отчета
```bash
curl -X GET http://localhost:8080/api/reports/spending/pdf \
  -H "Authorization: Bearer YOUR_ADMIN_TOKEN" \
  -o spending_report.pdf
```

### Скачивание PDF отчета для конкретного пользователя
```bash
curl -X GET http://localhost:8080/api/reports/spending/user/1/pdf \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -o user_spending_report.pdf
```

### Получение отчета топ-10 товаров
```bash
curl -X GET http://localhost:8080/api/reports/top-products \
  -H "Authorization: Bearer YOUR_ADMIN_TOKEN"
```

### Скачивание PDF отчета топ-10 товаров
```bash
curl -X GET http://localhost:8080/api/reports/top-products/pdf \
  -H "Authorization: Bearer YOUR_ADMIN_TOKEN" \
  -o top_products_report.pdf
``` 