import React, { useState } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import { Container, Row, Col, Card, Form, Button, Alert } from 'react-bootstrap';

const Login = ({ setUser }) => {
  const [formData, setFormData] = useState({
    email: '',
    password: ''
  });
  const [errors, setErrors] = useState([]);
  const [loading, setLoading] = useState(false);
  const navigate = useNavigate();

  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  const validateForm = () => {
    const errors = [];
    if (!formData.email.trim()) errors.push('Email обязателен');
    if (!formData.email.includes('@')) errors.push('Некорректный email');
    if (!formData.password) errors.push('Пароль обязателен');
    return errors;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const validationErrors = validateForm();
    if (validationErrors.length > 0) {
      setErrors(validationErrors);
      return;
    }

    setLoading(true);
    try {
      const response = await fetch('http://localhost:3001/users');
      const users = await response.json();
      const user = users.find(u => u.email === formData.email && u.password === formData.password);
      
      if (user) {
        localStorage.setItem('user', JSON.stringify(user));
        setUser(user);
        navigate('/events');
      } else {
        setErrors(['Неверный email или пароль']);
      }
    } catch (error) {
      setErrors(['Ошибка подключения к серверу']);
    }
    setLoading(false);
  };

  return (
    <Container>
      <Row className="justify-content-center">
        <Col md={6}>
          <Card>
            <Card.Body className="text-start">
              <Card.Title className="text-center mb-4">Вход</Card.Title>
              {errors.length > 0 && (
                <Alert variant="light" className="border text-danger">
                  {errors.map((error, index) => (
                    <div key={index}>{error}</div>
                  ))}
                </Alert>
              )}
              <Form onSubmit={handleSubmit}>
                <Form.Group className="mb-3">
                  <Form.Label>Email</Form.Label>
                  <Form.Control
                    type="email"
                    name="email"
                    value={formData.email}
                    onChange={handleChange}
                  />
                </Form.Group>
                <Form.Group className="mb-3">
                  <Form.Label>Пароль</Form.Label>
                  <Form.Control
                    type="password"
                    name="password"
                    value={formData.password}
                    onChange={handleChange}
                  />
                </Form.Group>
                <Button variant="dark" type="submit" className="w-100" disabled={loading}>
                  {loading ? 'Вход...' : 'Войти'}
                </Button>
              </Form>
              <div className="text-center mt-3">
                <Link to="/register">Нет аккаунта? Зарегистрируйтесь</Link>
              </div>
            </Card.Body>
          </Card>
        </Col>
      </Row>
    </Container>
  );
};

export default Login; 