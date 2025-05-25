import React, { useState, useEffect } from 'react';
import { Container, Row, Col, Card, Button, Alert, Badge } from 'react-bootstrap';
import { Link } from 'react-router-dom';

const Locations = ({ user }) => {
  const [locations, setLocations] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    fetchLocations();
  }, []);

  const fetchLocations = async () => {
    try {
      const response = await fetch('http://localhost:3001/locations');
      const data = await response.json();
      setLocations(data);
    } catch (error) {
      console.error('Ошибка загрузки локаций:', error);
    }
    setLoading(false);
  };

  const deleteLocation = async (id) => {
    if (window.confirm('Удалить локацию?')) {
      try {
        await fetch(`http://localhost:3001/locations/${id}`, {
          method: 'DELETE',
        });
        setLocations(locations.filter(location => location.id !== id));
      } catch (error) {
        console.error('Ошибка удаления:', error);
      }
    }
  };

  if (loading) return <div className="text-center">Загрузка...</div>;

  return (
    <Container>
      <div className="d-flex justify-content-between align-items-center mb-4">
        <h2>Локации</h2>
        <Button as={Link} to="/locations/new" variant="dark">
          Добавить локацию
        </Button>
      </div>

      {locations.length === 0 ? (
        <Alert variant="light" className="border">
          Локации не найдены. <Link to="/locations/new">Создайте первую локацию</Link>
        </Alert>
      ) : (
        <Row>
          {locations.map(location => (
            <Col key={location.id} md={6} className="mb-4">
              <Card className="h-100 border" style={{ minHeight: '280px' }}>
                <Card.Body className="d-flex flex-column text-start p-4">
                  <Card.Title className="mb-3">{location.name}</Card.Title>
                  <div className="mb-3" style={{ fontSize: '0.9rem' }}>
                    <div className="mb-1"><strong>Адрес:</strong> {location.address}</div>
                    <div className="mb-1"><strong>Вместимость:</strong> {location.capacity} человек</div>
                    <div className="mb-2"><strong>Описание:</strong> {location.description}</div>
                  </div>
                  {location.amenities && location.amenities.length > 0 && (
                    <div className="mb-3">
                      <strong>Удобства:</strong>
                      <div className="mt-1">
                        {location.amenities.map((amenity, index) => (
                          <Badge key={index} bg="light" text="dark" className="border me-1 mb-1">
                            {amenity}
                          </Badge>
                        ))}
                      </div>
                    </div>
                  )}
                  <div className="d-flex gap-2 mt-auto">
                    <Button as={Link} to={`/locations/edit/${location.id}`} variant="outline-dark" size="sm">
                      Редактировать
                    </Button>
                    <Button 
                      variant="outline-danger" 
                      size="sm"
                      onClick={() => deleteLocation(location.id)}
                    >
                      Удалить
                    </Button>
                  </div>
                </Card.Body>
              </Card>
            </Col>
          ))}
        </Row>
      )}
    </Container>
  );
};

export default Locations; 