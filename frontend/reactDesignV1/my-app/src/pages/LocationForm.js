import React, { useState, useEffect } from 'react';
import { useNavigate, useParams } from 'react-router-dom';
import { Container, Row, Col, Card, Form, Button, Alert, Badge, InputGroup } from 'react-bootstrap';
import { Location } from '../entities/Location';

const LocationForm = ({ user }) => {
  const [formData, setFormData] = useState({
    name: '',
    address: '',
    description: '',
    capacity: '',
    amenities: []
  });
  const [errors, setErrors] = useState([]);
  const [loading, setLoading] = useState(false);
  const [amenityInput, setAmenityInput] = useState('');
  const navigate = useNavigate();
  const { id } = useParams();
  const isEdit = !!id;

  useEffect(() => {
    if (isEdit) {
      fetchLocation();
    }
  }, [id, isEdit]);

  const fetchLocation = async () => {
    try {
      const response = await fetch(`http://localhost:3001/locations/${id}`);
      const location = await response.json();
      setFormData({
        name: location.name,
        address: location.address,
        description: location.description,
        capacity: location.capacity.toString(),
        amenities: location.amenities || []
      });
    } catch (error) {
      console.error('Ошибка загрузки локации:', error);
    }
  };

  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  const addAmenity = () => {
    if (amenityInput.trim() && !formData.amenities.includes(amenityInput.trim())) {
      setFormData({
        ...formData,
        amenities: [...formData.amenities, amenityInput.trim()]
      });
      setAmenityInput('');
    }
  };

  const removeAmenity = (amenity) => {
    setFormData({
      ...formData,
      amenities: formData.amenities.filter(a => a !== amenity)
    });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    
    const locationData = {
      ...formData,
      capacity: parseInt(formData.capacity)
    };
    
    const location = new Location(locationData);
    const validationErrors = location.validate();
    
    if (validationErrors.length > 0) {
      setErrors(validationErrors);
      return;
    }

    setLoading(true);
    try {
      const url = isEdit 
        ? `http://localhost:3001/locations/${id}`
        : 'http://localhost:3001/locations';
      
      const method = isEdit ? 'PUT' : 'POST';
      
      const dataToSend = isEdit 
        ? { ...locationData, id: id }
        : { ...locationData, id: Date.now().toString() };

      const response = await fetch(url, {
        method,
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(dataToSend),
      });

      if (response.ok) {
        navigate('/locations');
      } else {
        setErrors(['Ошибка при сохранении локации']);
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
                {isEdit ? 'Редактировать локацию' : 'Создать локацию'}
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
                    name="name"
                    value={formData.name}
                    onChange={handleChange}
                  />
                </Form.Group>
                <Form.Group className="mb-3">
                  <Form.Label>Адрес</Form.Label>
                  <Form.Control
                    type="text"
                    name="address"
                    value={formData.address}
                    onChange={handleChange}
                  />
                </Form.Group>
                <Form.Group className="mb-3">
                  <Form.Label>Описание</Form.Label>
                  <Form.Control
                    as="textarea"
                    rows={3}
                    name="description"
                    value={formData.description}
                    onChange={handleChange}
                  />
                </Form.Group>
                <Form.Group className="mb-3">
                  <Form.Label>Вместимость</Form.Label>
                  <Form.Control
                    type="number"
                    name="capacity"
                    min="1"
                    value={formData.capacity}
                    onChange={handleChange}
                  />
                </Form.Group>
                <Form.Group className="mb-3">
                  <Form.Label>Удобства</Form.Label>
                  <InputGroup className="mb-2">
                    <Form.Control
                      type="text"
                      value={amenityInput}
                      onChange={(e) => setAmenityInput(e.target.value)}
                      placeholder="Добавить удобство"
                    />
                    <Button variant="outline-secondary" onClick={addAmenity}>
                      Добавить
                    </Button>
                  </InputGroup>
                  <div>
                    {formData.amenities.map((amenity, index) => (
                      <Badge key={index} bg="light" text="dark" className="border me-1 mb-1">
                        {amenity}
                        <Button
                          variant="link"
                          size="sm"
                          className="p-0 ms-1 text-dark"
                          onClick={() => removeAmenity(amenity)}
                          style={{ fontSize: '0.6em', textDecoration: 'none' }}
                        >
                          ×
                        </Button>
                      </Badge>
                    ))}
                  </div>
                </Form.Group>
                <div className="d-flex gap-2">
                  <Button variant="dark" type="submit" disabled={loading}>
                    {loading ? 'Сохранение...' : 'Сохранить'}
                  </Button>
                  <Button
                    variant="outline-secondary"
                    onClick={() => navigate('/locations')}
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

export default LocationForm; 