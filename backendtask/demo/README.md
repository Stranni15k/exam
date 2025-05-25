# Internet Shop REST API

Полнофункциональный REST API для интернет-магазина, построенный на Spring Boot с JWT аутентификацией.

## 🚀 Возможности

- ✅ **Управление пользователями** - регистрация, аутентификация, профили
- ✅ **Каталог товаров** - CRUD операции, категории, поиск, пагинация  
- ✅ **Корзина покупок** - добавление, обновление, удаление товаров
- ✅ **Система заказов** - оформление, отслеживание статуса, отмена
- ✅ **Роли и права доступа** - USER, ADMIN
- ✅ **Отчеты** - продажи, популярные товары (только для администраторов)
- ✅ **Версионирование данных** - оптимистичная блокировка
- ✅ **Валидация** - полная валидация входных данных
- ✅ **Swagger документация** - интерактивная документация API

## 🛠 Технологии

- **Java 17**
- **Spring Boot 3.5.0** 
- **Spring Security** с JWT
- **Spring Data JPA** с Hibernate
- **H2 Database** (в памяти для демо)
- **OpenAPI/Swagger 3** для документации
- **Maven** для сборки

## 🏃 Быстрый старт

### 1. Клонирование и запуск

```bash
git clone <repository-url>
cd demo
mvn spring-boot:run
```

### 2. Доступ к приложению

- **API Base URL**: `http://localhost:8080/api`
- **Swagger UI**: `http://localhost:8080/swagger-ui.html`
- **H2 Console**: `http://localhost:8080/h2-console`
  - JDBC URL: `jdbc:h2:mem:shopdb`
  - Username: `sa`
  - Password: `password`

### 3. Тестовые аккаунты

При первом запуске автоматически создаются:

**Администратор:**
- Username: `admin`
- Password: `admin123`
- Email: `admin@shop.com`

**Пользователь:**
- Username: `user`  
- Password: `user123`
- Email: `user@example.com`

## 📚 API Документация

### Аутентификация

#### POST `/api/auth/register`
Регистрация нового пользователя.

```json
{
  "username": "newuser",
  "email": "user@example.com",
  "password": "password123",
  "firstName": "Имя",
  "lastName": "Фамилия",
  "phoneNumber": "+7 (900) 123-45-67",
  "address": "г. Москва, ул. Примерная, д. 1"
}
```

#### POST `/api/auth/login`
Аутентификация пользователя.

```json
{
  "username": "admin",
  "password": "admin123"
}
```

**Ответ:**
```json
{
  "token": "eyJhbGciOiJIUzI1NiJ9...",
  "type": "Bearer",
  "user": {
    "id": 1,
    "username": "admin",
    "email": "admin@shop.com",
    "fullName": "Администратор Системы",
    "role": "ADMIN"
  }
}
```

### Товары

#### GET `/api/products`
Получение списка товаров с пагинацией.

**Параметры:**
- `page` (int, default: 0) - номер страницы
- `size` (int, default: 12) - размер страницы  
- `categoryId` (Long, optional) - фильтр по категории
- `search` (String, optional) - поиск по названию

#### GET `/api/products/{id}`
Получение товара по ID.

#### POST `/api/products` 🔒 ADMIN
Создание нового товара.

```json
{
  "name": "iPhone 15",
  "description": "Новейший смартфон Apple",
  "price": 89999,
  "stockQuantity": 10,
  "categoryId": 1,
  "imageUrl": "https://example.com/image.jpg"
}
```

#### PUT `/api/products/{id}` 🔒 ADMIN
Обновление товара.

#### DELETE `/api/products/{id}` 🔒 ADMIN
Удаление товара.

### Категории

#### GET `/api/categories`
Получение всех категорий.

#### POST `/api/categories` 🔒 ADMIN
Создание новой категории.

```json
{
  "name": "Электроника",
  "description": "Электронные товары и гаджеты"
}
```

### Корзина

#### GET `/api/cart` 🔒 AUTH
Получение содержимого корзины текущего пользователя.

#### POST `/api/cart/add` 🔒 AUTH
Добавление товара в корзину.

```json
{
  "productId": 1,
  "quantity": 2
}
```

#### PUT `/api/cart/update` 🔒 AUTH
Обновление количества товара в корзине.

```json
{
  "productId": 1,
  "quantity": 3
}
```

#### DELETE `/api/cart/remove/{productId}` 🔒 AUTH
Удаление товара из корзины.

#### POST `/api/cart/checkout` 🔒 AUTH
Оформление заказа.

```json
{
  "shippingAddress": "г. Москва, ул. Доставки, д. 1",
  "paymentMethod": "Наличные"
}
```

### Заказы

#### GET `/api/orders` 🔒 AUTH
Получение заказов текущего пользователя.

#### GET `/api/orders/{id}` 🔒 AUTH
Получение заказа по ID.

#### POST `/api/orders/{id}/cancel` 🔒 AUTH
Отмена заказа.

### Администрирование

#### GET `/api/orders/admin/all` 🔒 ADMIN
Получение всех заказов.

#### PUT `/api/orders/admin/{id}/status` 🔒 ADMIN
Обновление статуса заказа.

```json
{
  "status": "CONFIRMED"
}
```

**Доступные статусы:**
- `PENDING` - В ожидании
- `CONFIRMED` - Подтвержден
- `SHIPPED` - Отправлен
- `DELIVERED` - Доставлен
- `CANCELLED` - Отменен

### Отчеты

#### GET `/api/reports/sales` 🔒 ADMIN
Отчет по продажам.

**Параметры:**
- `startDate` (String, optional) - дата начала (yyyy-MM-dd)
- `endDate` (String, optional) - дата окончания (yyyy-MM-dd)

#### GET `/api/reports/products` 🔒 ADMIN
Отчет по популярности товаров.

#### GET `/api/reports/dashboard` 🔒 ADMIN
Данные для дашборда администратора.

### Пользователи

#### GET `/api/users/profile` 🔒 AUTH
Получение профиля текущего пользователя.

#### PUT `/api/users/profile` 🔒 AUTH
Обновление профиля.

#### POST `/api/users/change-password` 🔒 AUTH
Изменение пароля.

```json
{
  "currentPassword": "oldpassword",
  "newPassword": "newpassword"
}
```

## 🔐 Авторизация

Для защищенных endpoints используйте JWT токен в заголовке:

```
Authorization: Bearer <your-jwt-token>
```

## 📊 Доменная модель

### Сущности:

1. **User** - Пользователи системы
2. **Category** - Категории товаров  
3. **Product** - Товары
4. **Order** - Заказы
5. **OrderItem** - Позиции заказа
6. **BaseEntity** - Базовая сущность с версионированием

### Связи:

- `User` ↔ `Order` (OneToMany/ManyToOne)
- `Category` ↔ `Product` (OneToMany/ManyToOne)  
- `Product` ↔ `OrderItem` (OneToMany/ManyToOne)
- `Order` ↔ `OrderItem` (OneToMany/ManyToOne)

## 🔧 Конфигурация

### application.properties

```properties
# Server
server.port=8080

# Database
spring.datasource.url=jdbc:h2:mem:shopdb
spring.jpa.hibernate.ddl-auto=create-drop

# CORS
cors.allowed-origins=http://localhost:3000,http://localhost:3001

# JWT
jwt.secret=myVerySecretKeyForJWTTokenGeneration
jwt.expiration=86400000
```

## 🚀 Развертывание

### Docker (будущая функция)

```dockerfile
FROM openjdk:17-jdk-slim
COPY target/demo-0.0.1-SNAPSHOT.jar app.jar
EXPOSE 8080
ENTRYPOINT ["java", "-jar", "/app.jar"]
```

## 🧪 Тестирование

### Примеры cURL

**Регистрация:**
```bash
curl -X POST http://localhost:8080/api/auth/register \
  -H "Content-Type: application/json" \
  -d '{"username":"testuser","email":"test@example.com","password":"password123","firstName":"Test","lastName":"User"}'
```

**Вход:**
```bash
curl -X POST http://localhost:8080/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"username":"admin","password":"admin123"}'
```

**Получение товаров:**
```bash
curl -X GET http://localhost:8080/api/products
```

## 📝 Лицензия

MIT License

## 👥 Контакты

Для вопросов и предложений создайте issue в репозитории. 

# Demo Spring Boot Application - Аутентификация и Авторизация

Это демонстрационное приложение с JWT аутентификацией и авторизацией пользователей.

## Запуск приложения

```bash
mvn spring-boot:run
```

Приложение будет доступно по адресу: `http://localhost:8080`

## API Endpoints

### Аутентификация

#### Регистрация пользователя
```
POST /api/auth/register
Content-Type: application/json

{
    "username": "user1",
    "password": "password123"
}
```

**Ответ:**
```json
{
    "token": "eyJhbGciOiJIUzI1NiJ9...",
    "username": "user1",
    "role": "USER"
}
```

#### Вход в систему
```
POST /api/auth/login
Content-Type: application/json

{
    "username": "user1",
    "password": "password123"
}
```

**Ответ:**
```json
{
    "token": "eyJhbGciOiJIUzI1NiJ9...",
    "username": "user1",
    "role": "USER"
}
```

### Защищенные endpoints

#### Получение профиля пользователя
```
GET /api/users/profile
Authorization: Bearer eyJhbGciOiJIUzI1NiJ9...
```

**Ответ:**
```
Hello, user1!
```

#### Админские данные (только для ADMIN)
```
GET /api/users/admin
Authorization: Bearer eyJhbGciOiJIUzI1NiJ9...
```

**Ответ:**
```
This is admin data!
```

## Валидация

- **username**: обязательное поле, от 3 до 50 символов
- **password**: обязательное поле, от 6 до 100 символов

## Роли пользователей

- **USER** - обычный пользователь (по умолчанию)
- **ADMIN** - администратор

## База данных

Приложение использует встроенную H2 базу данных. Консоль H2 доступна по адресу:
`http://localhost:8080/h2-console`

**Параметры подключения:**
- JDBC URL: `jdbc:h2:mem:shopdb`
- Username: `sa`
- Password: `password`

## Swagger Documentation

API документация доступна по адресу:
`http://localhost:8080/swagger-ui.html`

## Примеры использования с curl

### Регистрация
```bash
curl -X POST http://localhost:8080/api/auth/register \
  -H "Content-Type: application/json" \
  -d '{"username":"testuser","password":"password123"}'
```

### Вход
```bash
curl -X POST http://localhost:8080/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"username":"testuser","password":"password123"}'
```

### Получение профиля
```bash
curl -X GET http://localhost:8080/api/users/profile \
  -H "Authorization: Bearer YOUR_JWT_TOKEN"
``` 