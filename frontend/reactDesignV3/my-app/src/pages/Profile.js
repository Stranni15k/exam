import React, { useState } from 'react';
import { Container, Row, Col, Card, Form, Button, Alert, Badge } from 'react-bootstrap';
import { User } from '../entities/User';

const Profile = ({ user, setUser }) => {
  const [isEditing, setIsEditing] = useState(false);
  const [formData, setFormData] = useState({
    name: user.name,
    email: user.email,
    phone: user.phone || '',
    bio: user.bio || '',
    role: user.role
  });
  const [errors, setErrors] = useState([]);
  const [loading, setLoading] = useState(false);

  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    
    const updatedUser = new User({
      ...user,
      ...formData
    });
    
    const validationErrors = updatedUser.validate();
    if (validationErrors.length > 0) {
      setErrors(validationErrors);
      return;
    }

    setLoading(true);
    try {
      const response = await fetch(`http://localhost:3001/users/${user.id}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(updatedUser),
      });

      if (response.ok) {
        const updated = await response.json();
        setUser(updated);
        localStorage.setItem('user', JSON.stringify(updated));
        setIsEditing(false);
        setErrors([]);
      } else {
        setErrors(['Ошибка при обновлении профиля']);
      }
    } catch (error) {
      setErrors(['Ошибка подключения к серверу']);
    }
    setLoading(false);
  };

  const cancelEdit = () => {
    setFormData({
      name: user.name,
      email: user.email,
      phone: user.phone || '',
      bio: user.bio || '',
      role: user.role
    });
    setIsEditing(false);
    setErrors([]);
  };

  return (
    <Container>
      <Row className="justify-content-center">
        <Col md={8}>
          <Card>
            <Card.Body className="text-start">
              <div className="d-flex justify-content-between align-items-center mb-4">
                <Card.Title>Профиль</Card.Title>
                {!isEditing && (
                  <Button 
                    variant="outline-dark"
                    onClick={() => setIsEditing(true)}
                  >
                    Редактировать
                  </Button>
                )}
              </div>

              {errors.length > 0 && (
                <Alert variant="light" className="border text-danger">
                  {errors.map((error, index) => (
                    <div key={index}>{error}</div>
                  ))}
                </Alert>
              )}

              {isEditing ? (
                <Form onSubmit={handleSubmit}>
                  <Row>
                    <Col md={6}>
                      <Form.Group className="mb-3">
                        <Form.Label>Имя</Form.Label>
                        <Form.Control
                          type="text"
                          name="name"
                          value={formData.name}
                          onChange={handleChange}
                        />
                      </Form.Group>
                    </Col>
                    <Col md={6}>
                      <Form.Group className="mb-3">
                        <Form.Label>Email</Form.Label>
                        <Form.Control
                          type="email"
                          name="email"
                          value={formData.email}
                          onChange={handleChange}
                        />
                      </Form.Group>
                    </Col>
                  </Row>
                  <Row>
                    <Col md={6}>
                      <Form.Group className="mb-3">
                        <Form.Label>Телефон</Form.Label>
                        <Form.Control
                          type="tel"
                          name="phone"
                          value={formData.phone}
                          onChange={handleChange}
                        />
                      </Form.Group>
                    </Col>
                    <Col md={6}>
                      <Form.Group className="mb-3">
                        <Form.Label>Роль</Form.Label>
                        <Form.Select
                          name="role"
                          value={formData.role}
                          onChange={handleChange}
                        >
                          <option value="participant">Участник</option>
                          <option value="organizer">Организатор</option>
                        </Form.Select>
                      </Form.Group>
                    </Col>
                  </Row>
                  <Form.Group className="mb-3">
                    <Form.Label>О себе</Form.Label>
                    <Form.Control
                      as="textarea"
                      rows={4}
                      name="bio"
                      value={formData.bio}
                      onChange={handleChange}
                    />
                  </Form.Group>
                  <div className="d-flex gap-2">
                    <Button variant="dark" type="submit" disabled={loading}>
                      {loading ? 'Сохранение...' : 'Сохранить'}
                    </Button>
                    <Button
                      variant="outline-secondary"
                      onClick={cancelEdit}
                    >
                      Отмена
                    </Button>
                  </div>
                </Form>
              ) : (
                <div>
                  <Row className="mb-3">
                    <Col md={6}>
                      <strong>Имя:</strong> {user.name}
                    </Col>
                    <Col md={6}>
                      <strong>Email:</strong> {user.email}
                    </Col>
                  </Row>
                  <Row className="mb-3">
                    <Col md={6}>
                      <strong>Телефон:</strong> {user.phone || 'Не указан'}
                    </Col>
                    <Col md={6}>
                      <strong>Роль:</strong> 
                      <Badge bg={user.role === 'organizer' ? 'dark' : 'secondary'} className="ms-2">
                        {user.role === 'organizer' ? 'Организатор' : 'Участник'}
                      </Badge>
                    </Col>
                  </Row>
                  {user.bio && (
                    <div className="mb-3">
                      <strong>О себе:</strong>
                      <p className="mt-2">{user.bio}</p>
                    </div>
                  )}
                  <Row>
                    <Col md={6}>
                      <Card className="border">
                        <Card.Body className="text-center p-4">
                          <Card.Title as="h5">Созданные события</Card.Title>
                          <h2 className="text-dark">{user.organizedEvents?.length || 0}</h2>
                        </Card.Body>
                      </Card>
                    </Col>
                    <Col md={6}>
                      <Card className="border">
                        <Card.Body className="text-center p-4">
                          <Card.Title as="h5">Участие в событиях</Card.Title>
                          <h2 className="text-dark">{user.registeredEvents?.length || 0}</h2>
                        </Card.Body>
                      </Card>
                    </Col>
                  </Row>
                </div>
              )}
            </Card.Body>
          </Card>
        </Col>
      </Row>
    </Container>
  );
};

export default Profile; 