import React, { useState, useEffect } from 'react';
import { useNavigate, useParams } from 'react-router-dom';
import { Container, Row, Col, Card, Form, Button, Alert } from 'react-bootstrap';
import { Event } from '../entities/Event';

const EventForm = ({ user }) => {
  const [formData, setFormData] = useState({
    title: '',
    description: '',
    date: '',
    time: '',
    maxParticipants: '',
    category: '',
    locationId: ''
  });
  const [locations, setLocations] = useState([]);
  const [errors, setErrors] = useState([]);
  const [loading, setLoading] = useState(false);
  const navigate = useNavigate();
  const { id } = useParams();
  const isEdit = !!id;

  const categories = [
    'Лекция',
    'Мастер-класс',
    'Воркшоп',
    'Встреча',
    'Прогулка',
    'Конференция',
    'Семинар',
    'Другое'
  ];

  useEffect(() => {
    fetchLocations();
    if (isEdit) {
      fetchEvent();
    }
  }, [id, isEdit]);

  const fetchLocations = async () => {
    try {
      const response = await fetch('http://localhost:3001/locations');
      const data = await response.json();
      setLocations(data);
    } catch (error) {
      console.error('Ошибка загрузки локаций:', error);
    }
  };

  const fetchEvent = async () => {
    try {
      const response = await fetch(`http://localhost:3001/events/${id}`);
      const event = await response.json();
      setFormData({
        title: event.title,
        description: event.description,
        date: event.date,
        time: event.time,
        maxParticipants: event.maxParticipants.toString(),
        category: event.category,
        locationId: event.locationId.toString()
      });
    } catch (error) {
      console.error('Ошибка загрузки события:', error);
    }
  };

  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    
    const eventData = {
      ...formData,
      maxParticipants: parseInt(formData.maxParticipants),
      locationId: formData.locationId,
      organizerId: user.id
    };
    
    const event = new Event(eventData);
    const validationErrors = event.validate();
    
    if (validationErrors.length > 0) {
      setErrors(validationErrors);
      return;
    }

    setLoading(true);
    try {
      const url = isEdit 
        ? `http://localhost:3001/events/${id}`
        : 'http://localhost:3001/events';
      
      const method = isEdit ? 'PUT' : 'POST';
      
      const dataToSend = isEdit 
        ? { ...eventData, id: id, participants: [] }
        : { ...eventData, id: Date.now().toString(), participants: [] };

      const response = await fetch(url, {
        method,
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(dataToSend),
      });

      if (response.ok) {
        navigate('/events');
      } else {
        setErrors(['Ошибка при сохранении события']);
      }
    } catch (error) {
      setErrors(['Ошибка подключения к серверу']);
    }
    setLoading(false);
  };

  return (
    <Container>
      <Row className="justify-content-center">
        <Col md={8}>
          <Card>
            <Card.Body className="text-start">
              <Card.Title>
                {isEdit ? 'Редактировать событие' : 'Создать событие'}
              </Card.Title>
              {errors.length > 0 && (
                <Alert variant="light" className="border text-danger">
                  {errors.map((error, index) => (
                    <div key={index}>{error}</div>
                  ))}
                </Alert>
              )}
              <Form onSubmit={handleSubmit}>
                <Form.Group className="mb-3">
                  <Form.Label>Название</Form.Label>
                  <Form.Control
                    type="text"
                    name="title"
                    value={formData.title}
                    onChange={handleChange}
                  />
                </Form.Group>
                <Form.Group className="mb-3">
                  <Form.Label>Описание</Form.Label>
                  <Form.Control
                    as="textarea"
                    rows={4}
                    name="description"
                    value={formData.description}
                    onChange={handleChange}
                  />
                </Form.Group>
                <Row>
                  <Col md={6}>
                    <Form.Group className="mb-3">
                      <Form.Label>Дата</Form.Label>
                      <Form.Control
                        type="date"
                        name="date"
                        value={formData.date}
                        onChange={handleChange}
                      />
                    </Form.Group>
                  </Col>
                  <Col md={6}>
                    <Form.Group className="mb-3">
                      <Form.Label>Время</Form.Label>
                      <Form.Control
                        type="time"
                        name="time"
                        value={formData.time}
                        onChange={handleChange}
                      />
                    </Form.Group>
                  </Col>
                </Row>
                <Row>
                  <Col md={6}>
                    <Form.Group className="mb-3">
                      <Form.Label>Максимальное количество участников</Form.Label>
                      <Form.Control
                        type="number"
                        name="maxParticipants"
                        min="1"
                        value={formData.maxParticipants}
                        onChange={handleChange}
                      />
                    </Form.Group>
                  </Col>
                  <Col md={6}>
                    <Form.Group className="mb-3">
                      <Form.Label>Категория</Form.Label>
                      <Form.Select
                        name="category"
                        value={formData.category}
                        onChange={handleChange}
                      >
                        <option value="">Выберите категорию</option>
                        {categories.map(category => (
                          <option key={category} value={category}>{category}</option>
                        ))}
                      </Form.Select>
                    </Form.Group>
                  </Col>
                </Row>
                <Form.Group className="mb-3">
                  <Form.Label>Локация</Form.Label>
                  <Form.Select
                    name="locationId"
                    value={formData.locationId}
                    onChange={handleChange}
                  >
                    <option value="">Выберите локацию</option>
                    {locations.map(location => (
                      <option key={location.id} value={location.id}>
                        {location.name} - {location.address}
                      </option>
                    ))}
                  </Form.Select>
                  {locations.length === 0 && (
                    <Form.Text className="text-muted">
                      Нет доступных локаций. Сначала создайте локацию.
                    </Form.Text>
                  )}
                </Form.Group>
                <div className="d-flex gap-2">
                  <Button variant="dark" type="submit" disabled={loading}>
                    {loading ? 'Сохранение...' : 'Сохранить'}
                  </Button>
                  <Button
                    variant="outline-secondary"
                    onClick={() => navigate('/events')}
                  >
                    Отмена
                  </Button>
                </div>
              </Form>
            </Card.Body>
          </Card>
        </Col>
      </Row>
    </Container>
  );
};

export default EventForm; 