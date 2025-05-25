import React, { useState } from 'react';

// Компонент для отображения таблицы
const DataTable = ({ data, title, type }) => {
  if (!data) return null;

  const tableStyle = {
    border: '1px solid #ddd',
    borderCollapse: 'collapse',
    width: '100%',
    marginTop: '10px'
  };

  const cellStyle = {
    border: '1px solid #ddd',
    padding: '8px',
    textAlign: 'left'
  };

  const headerStyle = {
    ...cellStyle,
    backgroundColor: '#f2f2f2',
    fontWeight: 'bold'
  };

  if (type === 'categories' && Array.isArray(data)) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <thead>
            <tr>
              <th style={headerStyle}>ID</th>
              <th style={headerStyle}>Название</th>
              <th style={headerStyle}>Описание</th>
            </tr>
          </thead>
          <tbody>
            {data.map(item => (
              <tr key={item.id}>
                <td style={cellStyle}>{item.id}</td>
                <td style={cellStyle}>{item.name}</td>
                <td style={cellStyle}>{item.description || '-'}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'category' && data.id) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <tbody>
            <tr>
              <td style={headerStyle}>ID</td>
              <td style={cellStyle}>{data.id}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Название</td>
              <td style={cellStyle}>{data.name}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Описание</td>
              <td style={cellStyle}>{data.description || '-'}</td>
            </tr>
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'products' && Array.isArray(data)) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <thead>
            <tr>
              <th style={headerStyle}>ID</th>
              <th style={headerStyle}>Название</th>
              <th style={headerStyle}>Описание</th>
              <th style={headerStyle}>Цена</th>
              <th style={headerStyle}>Категория</th>
            </tr>
          </thead>
          <tbody>
            {data.map(item => (
              <tr key={item.id}>
                <td style={cellStyle}>{item.id}</td>
                <td style={cellStyle}>{item.name}</td>
                <td style={cellStyle}>{item.description || '-'}</td>
                <td style={cellStyle}>{item.price ? `${item.price} ₽` : '-'}</td>
                <td style={cellStyle}>{item.category?.name || '-'}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'product' && data.id) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <tbody>
            <tr>
              <td style={headerStyle}>ID</td>
              <td style={cellStyle}>{data.id}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Название</td>
              <td style={cellStyle}>{data.name}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Описание</td>
              <td style={cellStyle}>{data.description || '-'}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Цена</td>
              <td style={cellStyle}>{data.price ? `${data.price} ₽` : '-'}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Категория</td>
              <td style={cellStyle}>{data.category?.name || '-'}</td>
            </tr>
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'orders' && Array.isArray(data)) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <thead>
            <tr>
              <th style={headerStyle}>ID</th>
              <th style={headerStyle}>Пользователь</th>
              <th style={headerStyle}>Статус</th>
              <th style={headerStyle}>Дата создания</th>
              <th style={headerStyle}>Общая сумма</th>
            </tr>
          </thead>
          <tbody>
            {data.map(item => (
              <tr key={item.id}>
                <td style={cellStyle}>{item.id}</td>
                <td style={cellStyle}>{item.user?.username || item.userId || '-'}</td>
                <td style={cellStyle}>{item.status}</td>
                <td style={cellStyle}>{item.createdAt ? new Date(item.createdAt).toLocaleString() : '-'}</td>
                <td style={cellStyle}>{item.totalAmount ? `${item.totalAmount} ₽` : '-'}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'order' && data.id) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <tbody>
            <tr>
              <td style={headerStyle}>ID</td>
              <td style={cellStyle}>{data.id}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Пользователь</td>
              <td style={cellStyle}>{data.user?.username || data.userId || '-'}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Статус</td>
              <td style={cellStyle}>{data.status}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Дата создания</td>
              <td style={cellStyle}>{data.createdAt ? new Date(data.createdAt).toLocaleString() : '-'}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Общая сумма</td>
              <td style={cellStyle}>{data.totalAmount ? `${data.totalAmount} ₽` : '-'}</td>
            </tr>
          </tbody>
        </table>
        {data.orderItems && data.orderItems.length > 0 && (
          <div style={{marginTop: '10px'}}>
            <h5>Товары в заказе:</h5>
            <table style={tableStyle}>
              <thead>
                <tr>
                  <th style={headerStyle}>Товар</th>
                  <th style={headerStyle}>Количество</th>
                  <th style={headerStyle}>Цена</th>
                </tr>
              </thead>
              <tbody>
                {data.orderItems.map((item, index) => (
                  <tr key={index}>
                    <td style={cellStyle}>{item.product?.name || '-'}</td>
                    <td style={cellStyle}>{item.quantity}</td>
                    <td style={cellStyle}>{item.price ? `${item.price} ₽` : '-'}</td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        )}
      </div>
    );
  }

  if (type === 'users' && Array.isArray(data)) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <thead>
            <tr>
              <th style={headerStyle}>ID</th>
              <th style={headerStyle}>Username</th>
              <th style={headerStyle}>Email</th>
              <th style={headerStyle}>Роль</th>
              <th style={headerStyle}>Дата создания</th>
            </tr>
          </thead>
          <tbody>
            {data.map(item => (
              <tr key={item.id}>
                <td style={cellStyle}>{item.id}</td>
                <td style={cellStyle}>{item.username}</td>
                <td style={cellStyle}>{item.email}</td>
                <td style={cellStyle}>{item.role}</td>
                <td style={cellStyle}>{item.createdAt ? new Date(item.createdAt).toLocaleString() : '-'}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'user' && data.id) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <tbody>
            <tr>
              <td style={headerStyle}>ID</td>
              <td style={cellStyle}>{data.id}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Username</td>
              <td style={cellStyle}>{data.username}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Email</td>
              <td style={cellStyle}>{data.email}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Роль</td>
              <td style={cellStyle}>{data.role}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Дата создания</td>
              <td style={cellStyle}>{data.createdAt ? new Date(data.createdAt).toLocaleString() : '-'}</td>
            </tr>
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'profiles' && Array.isArray(data)) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <thead>
            <tr>
              <th style={headerStyle}>ID</th>
              <th style={headerStyle}>Имя</th>
              <th style={headerStyle}>Фамилия</th>
              <th style={headerStyle}>Телефон</th>
              <th style={headerStyle}>Адрес</th>
              <th style={headerStyle}>Пользователь</th>
            </tr>
          </thead>
          <tbody>
            {data.map(item => (
              <tr key={item.id}>
                <td style={cellStyle}>{item.id}</td>
                <td style={cellStyle}>{item.firstName || '-'}</td>
                <td style={cellStyle}>{item.lastName || '-'}</td>
                <td style={cellStyle}>{item.phoneNumber || '-'}</td>
                <td style={cellStyle}>{item.address || '-'}</td>
                <td style={cellStyle}>{item.user?.username || '-'}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'profile' && data.id) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <tbody>
            <tr>
              <td style={headerStyle}>ID</td>
              <td style={cellStyle}>{data.id}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Имя</td>
              <td style={cellStyle}>{data.firstName || '-'}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Фамилия</td>
              <td style={cellStyle}>{data.lastName || '-'}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Телефон</td>
              <td style={cellStyle}>{data.phoneNumber || '-'}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Адрес</td>
              <td style={cellStyle}>{data.address || '-'}</td>
            </tr>
            <tr>
              <td style={headerStyle}>Пользователь</td>
              <td style={cellStyle}>{data.user?.username || '-'}</td>
            </tr>
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'spending-report' && data.userSpendingList) {
    return (
      <div>
        <h4>{title}</h4>
        <div style={{marginBottom: '10px'}}>
          <strong>Общая сумма трат: {data.totalSpending ? `${data.totalSpending} ₽` : '0 ₽'}</strong>
        </div>
        <table style={tableStyle}>
          <thead>
            <tr>
              <th style={headerStyle}>Пользователь</th>
              <th style={headerStyle}>Email</th>
              <th style={headerStyle}>Сумма трат</th>
              <th style={headerStyle}>Количество заказов</th>
            </tr>
          </thead>
          <tbody>
            {data.userSpendingList.map(item => (
              <tr key={item.userId}>
                <td style={cellStyle}>{item.username}</td>
                <td style={cellStyle}>{item.email}</td>
                <td style={cellStyle}>{item.totalSpent ? `${item.totalSpent} ₽` : '0 ₽'}</td>
                <td style={cellStyle}>{item.orderCount || 0}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    );
  }

  if (type === 'top-products-report' && data.topProductsList) {
    return (
      <div>
        <h4>{title}</h4>
        <table style={tableStyle}>
          <thead>
            <tr>
              <th style={headerStyle}>Позиция</th>
              <th style={headerStyle}>Товар</th>
              <th style={headerStyle}>Категория</th>
              <th style={headerStyle}>Количество продаж</th>
              <th style={headerStyle}>Общая выручка</th>
            </tr>
          </thead>
          <tbody>
            {data.topProductsList.map((item, index) => (
              <tr key={item.productId}>
                <td style={cellStyle}>{index + 1}</td>
                <td style={cellStyle}>{item.productName}</td>
                <td style={cellStyle}>{item.categoryName || '-'}</td>
                <td style={cellStyle}>{item.totalSold}</td>
                <td style={cellStyle}>{item.totalRevenue ? `${item.totalRevenue} ₽` : '0 ₽'}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    );
  }

  return null;
};

function App() {
  const [baseUrl, setBaseUrl] = useState('http://localhost:8080');
  const [token, setToken] = useState(localStorage.getItem('authToken') || '');
  const [response, setResponse] = useState('');
  const [loading, setLoading] = useState(false);
  const [visualData, setVisualData] = useState({});

  // Обновление токена
  const updateToken = (newToken) => {
    setToken(newToken);
    if (newToken) {
      localStorage.setItem('authToken', newToken);
    } else {
      localStorage.removeItem('authToken');
    }
  };

  // Универсальная функция для API запросов
  const makeRequest = async (endpoint, options = {}) => {
    setLoading(true);
    setResponse('');
    setVisualData({});
    
    try {
      const url = `${baseUrl}${endpoint}`;
      const config = {
        headers: {
          'Content-Type': 'application/json',
          ...options.headers
        },
        ...options
      };

      if (token && !options.noAuth) {
        config.headers['Authorization'] = `Bearer ${token}`;
      }

      const res = await fetch(url, config);
      
      let data;
      try {
        data = await res.json();
      } catch {
        data = await res.text();
      }

      const result = {
        status: res.status,
        success: res.ok,
        data: data
      };

      setResponse(JSON.stringify(result, null, 2));
      
      // Сохраняем данные для визуализации
      if (res.ok && data && typeof data === 'object') {
        let visualType = '';
        let visualTitle = '';
        
        if (endpoint === '/api/categories') {
          visualType = 'categories';
          visualTitle = 'Список категорий';
        } else if (endpoint.match(/^\/api\/categories\/\d+$/)) {
          visualType = 'category';
          visualTitle = 'Информация о категории';
        } else if (endpoint === '/api/products') {
          visualType = 'products';
          visualTitle = 'Список продуктов';
        } else if (endpoint.match(/^\/api\/products\/\d+$/)) {
          visualType = 'product';
          visualTitle = 'Информация о продукте';
        } else if (endpoint === '/api/orders' || endpoint === '/api/orders/my') {
          visualType = 'orders';
          visualTitle = endpoint === '/api/orders/my' ? 'Мои заказы' : 'Все заказы';
        } else if (endpoint.match(/^\/api\/orders\/\d+$/)) {
          visualType = 'order';
          visualTitle = 'Информация о заказе';
        } else if (endpoint === '/api/users') {
          visualType = 'users';
          visualTitle = 'Список пользователей';
        } else if (endpoint.match(/^\/api\/users\/\d+$/)) {
          visualType = 'user';
          visualTitle = 'Информация о пользователе';
        } else if (endpoint === '/api/profiles') {
          visualType = 'profiles';
          visualTitle = 'Список профилей';
        } else if (endpoint.match(/^\/api\/profiles\/\d+$/) || endpoint.match(/^\/api\/profiles\/user\/\d+$/)) {
          visualType = 'profile';
          visualTitle = 'Информация о профиле';
        } else if (endpoint === '/api/reports/spending' || endpoint.match(/^\/api\/reports\/spending\/user\/\d+$/)) {
          visualType = 'spending-report';
          visualTitle = endpoint === '/api/reports/spending' ? 'Отчет о тратах всех пользователей' : 'Отчет о тратах пользователя';
        } else if (endpoint === '/api/reports/top-products') {
          visualType = 'top-products-report';
          visualTitle = 'Топ-10 товаров';
        }
        
        if (visualType) {
          setVisualData({
            type: visualType,
            title: visualTitle,
            data: data,
            endpoint: endpoint
          });
        }
      }
      
      // Если это успешный логин, сохраняем токен
      if (res.ok && data && data.token && endpoint === '/api/auth/login') {
        updateToken(data.token);
      }
      
    } catch (error) {
      setResponse(`Ошибка: ${error.message}`);
      setVisualData({});
    } finally {
      setLoading(false);
    }
  };

  const logout = () => {
    updateToken('');
    setResponse('');
  };

  return (
    <div style={{padding: '20px', fontFamily: 'Arial, sans-serif'}}>
      <h1>Spring Boot API Demo</h1>
      
      {/* Конфигурация */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Конфигурация</h2>
        <label>
          Base URL: 
          <input 
            type="text" 
            value={baseUrl} 
            onChange={(e) => setBaseUrl(e.target.value)}
            style={{marginLeft: '10px', width: '300px'}}
          />
        </label>
        <div style={{marginTop: '10px'}}>
          Статус: {token ? <span style={{color: 'green'}}>Авторизован</span> : <span style={{color: 'red'}}>Не авторизован</span>}
          {token && <button onClick={logout} style={{marginLeft: '10px'}}>Выйти</button>}
        </div>
      </div>

      {/* Аутентификация */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Аутентификация</h2>
        
        <h3>Регистрация</h3>
        <form onSubmit={(e) => {
          e.preventDefault();
          const formData = new FormData(e.target);
          const data = {
            username: formData.get('regUsername'),
            email: formData.get('regEmail'),
            password: formData.get('regPassword')
          };
          makeRequest('/api/auth/register', {
            method: 'POST',
            body: JSON.stringify(data),
            noAuth: true
          });
        }}>
          <input name="regUsername" placeholder="Username" required />
          <input name="regEmail" type="email" placeholder="Email" required />
          <input name="regPassword" type="password" placeholder="Password" required />
          <button type="submit" disabled={loading}>Зарегистрироваться</button>
        </form>

        <h3>Вход</h3>
        <form onSubmit={(e) => {
          e.preventDefault();
          const formData = new FormData(e.target);
          const data = {
            username: formData.get('loginUsername'),
            password: formData.get('loginPassword')
          };
          makeRequest('/api/auth/login', {
            method: 'POST',
            body: JSON.stringify(data),
            noAuth: true
          });
        }}>
          <input name="loginUsername" placeholder="Username" required />
          <input name="loginPassword" type="password" placeholder="Password" required />
          <button type="submit" disabled={loading}>Войти</button>
        </form>
      </div>

      {/* Категории */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Категории</h2>
        
        <button onClick={() => makeRequest('/api/categories')} disabled={loading}>
          GET все категории
        </button>
        
        <form onSubmit={(e) => {
          e.preventDefault();
          const id = new FormData(e.target).get('catId');
          makeRequest(`/api/categories/${id}`);
        }} style={{display: 'inline', marginLeft: '10px'}}>
          <input name="catId" placeholder="ID" required />
          <button type="submit" disabled={loading}>GET по ID</button>
        </form>

        <h3>Создать категорию (ADMIN)</h3>
        <form onSubmit={(e) => {
          e.preventDefault();
          const formData = new FormData(e.target);
          const data = {
            name: formData.get('catName'),
            description: formData.get('catDesc')
          };
          makeRequest('/api/categories', {
            method: 'POST',
            body: JSON.stringify(data)
          });
        }}>
          <input name="catName" placeholder="Название" required />
          <input name="catDesc" placeholder="Описание" />
          <button type="submit" disabled={loading || !token}>Создать</button>
        </form>

        <h3>Обновить категорию (ADMIN)</h3>
        <form onSubmit={(e) => {
          e.preventDefault();
          const formData = new FormData(e.target);
          const id = formData.get('updateCatId');
          const data = {
            name: formData.get('updateCatName'),
            description: formData.get('updateCatDesc')
          };
          makeRequest(`/api/categories/${id}`, {
            method: 'PUT',
            body: JSON.stringify(data)
          });
        }}>
          <input name="updateCatId" placeholder="ID" required />
          <input name="updateCatName" placeholder="Новое название" required />
          <input name="updateCatDesc" placeholder="Новое описание" />
          <button type="submit" disabled={loading || !token}>Обновить</button>
        </form>

        <h3>Удалить категорию (ADMIN)</h3>
        <form onSubmit={(e) => {
          e.preventDefault();
          const id = new FormData(e.target).get('deleteCatId');
          makeRequest(`/api/categories/${id}`, { method: 'DELETE' });
        }}>
          <input name="deleteCatId" placeholder="ID" required />
          <button type="submit" disabled={loading || !token}>Удалить</button>
        </form>
        
        {/* Визуализация данных категорий */}
        {visualData.type && (visualData.type === 'categories' || visualData.type === 'category') && (
          <DataTable 
            data={visualData.data} 
            title={visualData.title} 
            type={visualData.type} 
          />
        )}
      </div>

      {/* Продукты */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Продукты</h2>
        
        <button onClick={() => makeRequest('/api/products')} disabled={loading}>
          GET все продукты
        </button>
        
        <form onSubmit={(e) => {
          e.preventDefault();
          const id = new FormData(e.target).get('prodId');
          makeRequest(`/api/products/${id}`);
        }} style={{display: 'inline', marginLeft: '10px'}}>
          <input name="prodId" placeholder="ID" required />
          <button type="submit" disabled={loading}>GET по ID</button>
        </form>

        <h3>Создать продукт (ADMIN)</h3>
        <form onSubmit={(e) => {
          e.preventDefault();
          const formData = new FormData(e.target);
          const data = {
            name: formData.get('prodName'),
            description: formData.get('prodDesc'),
            price: parseFloat(formData.get('prodPrice')) || 0,
            categoryId: parseInt(formData.get('prodCatId')) || null
          };
          makeRequest('/api/products', {
            method: 'POST',
            body: JSON.stringify(data)
          });
        }}>
          <input name="prodName" placeholder="Название" required />
          <input name="prodDesc" placeholder="Описание" />
          <input name="prodPrice" type="number" step="0.01" placeholder="Цена" required />
          <input name="prodCatId" type="number" placeholder="ID категории" />
          <button type="submit" disabled={loading || !token}>Создать</button>
        </form>
        
        {/* Визуализация данных продуктов */}
        {visualData.type && (visualData.type === 'products' || visualData.type === 'product') && (
          <DataTable 
            data={visualData.data} 
            title={visualData.title} 
            type={visualData.type} 
          />
        )}
      </div>

      {/* Заказы */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Заказы</h2>
        
        <button onClick={() => makeRequest('/api/orders')} disabled={loading || !token}>
          GET все заказы (ADMIN)
        </button>
        
        <button onClick={() => makeRequest('/api/orders/my')} disabled={loading || !token} style={{marginLeft: '10px'}}>
          GET мои заказы
        </button>
        
        <form onSubmit={(e) => {
          e.preventDefault();
          const id = new FormData(e.target).get('orderId');
          makeRequest(`/api/orders/${id}`);
        }} style={{display: 'inline', marginLeft: '10px'}}>
          <input name="orderId" placeholder="ID" required />
          <button type="submit" disabled={loading || !token}>GET по ID</button>
        </form>

        <h3>Создать заказ</h3>
        <form onSubmit={(e) => {
          e.preventDefault();
          const formData = new FormData(e.target);
          const data = {
            userId: parseInt(formData.get('orderUserId')) || null,
            status: formData.get('orderStatus')
          };
          makeRequest('/api/orders', {
            method: 'POST',
            body: JSON.stringify(data)
          });
        }}>
          <input name="orderUserId" type="number" placeholder="ID пользователя" />
          <select name="orderStatus" required>
            <option value="PENDING">PENDING</option>
            <option value="PROCESSING">PROCESSING</option>
            <option value="SHIPPED">SHIPPED</option>
            <option value="DELIVERED">DELIVERED</option>
            <option value="CANCELLED">CANCELLED</option>
          </select>
          <button type="submit" disabled={loading || !token}>Создать</button>
        </form>
        
        {/* Визуализация данных заказов */}
        {visualData.type && (visualData.type === 'orders' || visualData.type === 'order') && (
          <DataTable 
            data={visualData.data} 
            title={visualData.title} 
            type={visualData.type} 
          />
        )}
      </div>

      {/* Пользователи */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Пользователи</h2>
        
        <button onClick={() => makeRequest('/api/users')} disabled={loading || !token}>
          GET все пользователи (ADMIN)
        </button>
        
        <form onSubmit={(e) => {
          e.preventDefault();
          const id = new FormData(e.target).get('userId');
          makeRequest(`/api/users/${id}`);
        }} style={{display: 'inline', marginLeft: '10px'}}>
          <input name="userId" placeholder="ID" required />
          <button type="submit" disabled={loading || !token}>GET по ID</button>
        </form>
        
        {/* Визуализация данных пользователей */}
        {visualData.type && (visualData.type === 'users' || visualData.type === 'user') && (
          <DataTable 
            data={visualData.data} 
            title={visualData.title} 
            type={visualData.type} 
          />
        )}
      </div>

      {/* Профили */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Профили пользователей</h2>
        
        <button onClick={() => makeRequest('/api/profiles')} disabled={loading || !token}>
          GET все профили (ADMIN)
        </button>
        
        <form onSubmit={(e) => {
          e.preventDefault();
          const id = new FormData(e.target).get('profileId');
          makeRequest(`/api/profiles/${id}`);
        }} style={{display: 'inline', marginLeft: '10px'}}>
          <input name="profileId" placeholder="ID профиля" required />
          <button type="submit" disabled={loading || !token}>GET по ID</button>
        </form>

        <form onSubmit={(e) => {
          e.preventDefault();
          const id = new FormData(e.target).get('profileUserId');
          makeRequest(`/api/profiles/user/${id}`);
        }} style={{display: 'inline', marginLeft: '10px'}}>
          <input name="profileUserId" placeholder="ID пользователя" required />
          <button type="submit" disabled={loading || !token}>GET по User ID</button>
        </form>
        
        {/* Визуализация данных профилей */}
        {visualData.type && (visualData.type === 'profiles' || visualData.type === 'profile') && (
          <DataTable 
            data={visualData.data} 
            title={visualData.title} 
            type={visualData.type} 
          />
        )}
      </div>

      {/* Отчеты */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Отчеты (ADMIN)</h2>
        
        <h3>Отчеты о тратах</h3>
        <div style={{marginBottom: '15px'}}>
          <button onClick={() => makeRequest('/api/reports/spending')} disabled={loading || !token}>
            GET отчет о тратах всех пользователей (JSON)
          </button>
          
          <button 
            onClick={async () => {
              setLoading(true);
              try {
                const url = `${baseUrl}/api/reports/spending/pdf`;
                const config = {
                  headers: {
                    'Authorization': `Bearer ${token}`
                  }
                };
                
                const res = await fetch(url, config);
                if (res.ok) {
                  const blob = await res.blob();
                  const downloadUrl = window.URL.createObjectURL(blob);
                  const link = document.createElement('a');
                  link.href = downloadUrl;
                  link.download = `spending_report_${new Date().toISOString().slice(0,19).replace(/:/g, '-')}.pdf`;
                  document.body.appendChild(link);
                  link.click();
                  link.remove();
                  window.URL.revokeObjectURL(downloadUrl);
                  setResponse('PDF файл успешно скачан');
                } else {
                  setResponse(`Ошибка скачивания: ${res.status} ${res.statusText}`);
                }
              } catch (error) {
                setResponse(`Ошибка: ${error.message}`);
              } finally {
                setLoading(false);
              }
            }} 
            disabled={loading || !token}
            style={{marginLeft: '10px'}}
          >
            Скачать PDF отчет о тратах всех пользователей
          </button>
        </div>

        <div style={{marginBottom: '15px'}}>
          <form onSubmit={(e) => {
            e.preventDefault();
            const userId = new FormData(e.target).get('spendingUserId');
            makeRequest(`/api/reports/spending/user/${userId}`);
          }} style={{display: 'inline'}}>
            <input name="spendingUserId" placeholder="ID пользователя" required />
            <button type="submit" disabled={loading || !token}>GET отчет о тратах пользователя (JSON)</button>
          </form>
          
          <form onSubmit={async (e) => {
            e.preventDefault();
            const userId = new FormData(e.target).get('spendingUserIdPdf');
            setLoading(true);
            try {
              const url = `${baseUrl}/api/reports/spending/user/${userId}/pdf`;
              const config = {
                headers: {
                  'Authorization': `Bearer ${token}`
                }
              };
              
              const res = await fetch(url, config);
              if (res.ok) {
                const blob = await res.blob();
                const downloadUrl = window.URL.createObjectURL(blob);
                const link = document.createElement('a');
                link.href = downloadUrl;
                link.download = `user_${userId}_spending_report_${new Date().toISOString().slice(0,19).replace(/:/g, '-')}.pdf`;
                document.body.appendChild(link);
                link.click();
                link.remove();
                window.URL.revokeObjectURL(downloadUrl);
                setResponse('PDF файл успешно скачан');
              } else {
                setResponse(`Ошибка скачивания: ${res.status} ${res.statusText}`);
              }
            } catch (error) {
              setResponse(`Ошибка: ${error.message}`);
            } finally {
              setLoading(false);
            }
          }} style={{display: 'inline', marginLeft: '10px'}}>
            <input name="spendingUserIdPdf" placeholder="ID пользователя" required />
            <button type="submit" disabled={loading || !token}>Скачать PDF отчет пользователя</button>
          </form>
        </div>

        <h3>Отчет топ-10 товаров</h3>
        <div style={{marginBottom: '15px'}}>
          <button onClick={() => makeRequest('/api/reports/top-products')} disabled={loading || !token}>
            GET топ-10 товаров (JSON)
          </button>
          
          <button 
            onClick={async () => {
              setLoading(true);
              try {
                const url = `${baseUrl}/api/reports/top-products/pdf`;
                const config = {
                  headers: {
                    'Authorization': `Bearer ${token}`
                  }
                };
                
                const res = await fetch(url, config);
                if (res.ok) {
                  const blob = await res.blob();
                  const downloadUrl = window.URL.createObjectURL(blob);
                  const link = document.createElement('a');
                  link.href = downloadUrl;
                  link.download = `top_products_report_${new Date().toISOString().slice(0,19).replace(/:/g, '-')}.pdf`;
                  document.body.appendChild(link);
                  link.click();
                  link.remove();
                  window.URL.revokeObjectURL(downloadUrl);
                  setResponse('PDF файл успешно скачан');
                } else {
                  setResponse(`Ошибка скачивания: ${res.status} ${res.statusText}`);
                }
              } catch (error) {
                setResponse(`Ошибка: ${error.message}`);
              } finally {
                setLoading(false);
              }
            }} 
            disabled={loading || !token}
            style={{marginLeft: '10px'}}
          >
            Скачать PDF отчет топ-10 товаров
          </button>
        </div>
        
        {/* Визуализация данных отчетов */}
        {visualData.type && (visualData.type === 'spending-report' || visualData.type === 'top-products-report') && (
          <DataTable 
            data={visualData.data} 
            title={visualData.title} 
            type={visualData.type} 
          />
        )}
      </div>

      {/* Ответ */}
      <div style={{border: '1px solid #ccc', padding: '10px', margin: '10px 0'}}>
        <h2>Ответ от сервера</h2>
        {loading && <p>Загрузка...</p>}
        <pre style={{background: '#f5f5f5', padding: '10px', whiteSpace: 'pre-wrap'}}>
          {response || 'Ответов пока нет'}
        </pre>
      </div>
    </div>
  );
}

export default App;
