import React, { useState, useEffect } from 'react';
import { Container, Row, Col, Card, Button, ButtonGroup, Alert } from 'react-bootstrap';
import { Link } from 'react-router-dom';

const Events = ({ user }) => {
  const [events, setEvents] = useState([]);
  const [locations, setLocations] = useState([]);
  const [loading, setLoading] = useState(true);
  const [filter, setFilter] = useState('all'); // all, my, registered

  useEffect(() => {
    fetchData();
  }, []);

  const fetchData = async () => {
    try {
      const [eventsResponse, locationsResponse] = await Promise.all([
        fetch('http://localhost:3001/events'),
        fetch('http://localhost:3001/locations')
      ]);
      
      const eventsData = await eventsResponse.json();
      const locationsData = await locationsResponse.json();
      
      setEvents(eventsData);
      setLocations(locationsData);
    } catch (error) {
      console.error('Ошибка загрузки данных:', error);
    }
    setLoading(false);
  };

  const deleteEvent = async (id) => {
    if (window.confirm('Удалить событие?')) {
      try {
        await fetch(`http://localhost:3001/events/${id}`, {
          method: 'DELETE',
        });
        setEvents(events.filter(event => event.id !== id));
      } catch (error) {
        console.error('Ошибка удаления:', error);
      }
    }
  };

  const registerForEvent = async (eventId) => {
    try {
      const event = events.find(e => e.id === eventId.toString());
      const updatedParticipants = [...(event.participants || []), user.id.toString()];
      
      await fetch(`http://localhost:3001/events/${eventId}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          ...event,
          participants: updatedParticipants
        }),
      });

      setEvents(events.map(e => 
        e.id === eventId.toString()
          ? { ...e, participants: updatedParticipants }
          : e
      ));
    } catch (error) {
      console.error('Ошибка регистрации:', error);
    }
  };

  const unregisterFromEvent = async (eventId) => {
    try {
      const event = events.find(e => e.id === eventId.toString());
      const updatedParticipants = (event.participants || []).filter(id => id !== user.id.toString());
      
      await fetch(`http://localhost:3001/events/${eventId}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          ...event,
          participants: updatedParticipants
        }),
      });

      setEvents(events.map(e => 
        e.id === eventId.toString()
          ? { ...e, participants: updatedParticipants }
          : e
      ));
    } catch (error) {
      console.error('Ошибка отмены регистрации:', error);
    }
  };

  const getLocationName = (locationId) => {
    const location = locations.find(l => l.id === locationId.toString());
    return location ? location.name : 'Неизвестная локация';
  };

  const isUserRegistered = (event) => {
    return (event.participants || []).includes(user.id.toString());
  };

  const isEventFull = (event) => {
    return (event.participants || []).length >= event.maxParticipants;
  };

  const filteredEvents = events.filter(event => {
    if (filter === 'my') return event.organizerId === user.id.toString();
    if (filter === 'registered') return isUserRegistered(event);
    return true;
  });

  if (loading) return <div className="text-center">Загрузка...</div>;

  return (
    <Container>
      <div className="d-flex justify-content-between align-items-center mb-4">
        <h2>События</h2>
        <Button as={Link} to="/events/new" variant="dark">
          Создать событие
        </Button>
      </div>

      <div className="mb-4">
        <ButtonGroup>
          <Button
            variant={filter === 'all' ? 'dark' : 'outline-secondary'}
            onClick={() => setFilter('all')}
          >
            Все события
          </Button>
          <Button
            variant={filter === 'my' ? 'dark' : 'outline-secondary'}
            onClick={() => setFilter('my')}
          >
            Мои события
          </Button>
          <Button
            variant={filter === 'registered' ? 'dark' : 'outline-secondary'}
            onClick={() => setFilter('registered')}
          >
            Мои регистрации
          </Button>
        </ButtonGroup>
      </div>

      {filteredEvents.length === 0 ? (
        <Alert variant="light" className="border">
          События не найдены. <Link to="/events/new">Создайте первое событие</Link>
        </Alert>
      ) : (
        <Row>
          {filteredEvents.map(event => (
            <Col key={event.id} md={6} className="mb-4">
              <Card className="h-100 border" style={{ minHeight: '300px' }}>
                <Card.Body className="d-flex flex-column text-start p-4">
                  <Card.Title className="mb-3">{event.title}</Card.Title>
                  <Card.Text className="text-muted mb-3">{event.description}</Card.Text>
                  <div className="mb-3" style={{ fontSize: '0.9rem' }}>
                    <div className="mb-1"><strong>Дата:</strong> {event.date} в {event.time}</div>
                    <div className="mb-1"><strong>Локация:</strong> {getLocationName(event.locationId)}</div>
                    <div className="mb-1"><strong>Категория:</strong> {event.category}</div>
                    <div><strong>Участники:</strong> {(event.participants || []).length} / {event.maxParticipants}</div>
                  </div>
                  
                  <div className="d-flex gap-2 mt-auto">
                    {event.organizerId === user.id.toString() ? (
                      <>
                        <Button as={Link} to={`/events/edit/${event.id}`} variant="outline-dark" size="sm">
                          Редактировать
                        </Button>
                        <Button 
                          variant="outline-danger" 
                          size="sm"
                          onClick={() => deleteEvent(event.id)}
                        >
                          Удалить
                        </Button>
                      </>
                    ) : (
                      <>
                        {isUserRegistered(event) ? (
                          <Button 
                            variant="outline-danger" 
                            size="sm"
                            onClick={() => unregisterFromEvent(event.id)}
                          >
                            Отменить регистрацию
                          </Button>
                        ) : (
                          <Button 
                            variant="dark" 
                            size="sm"
                            disabled={isEventFull(event)}
                            onClick={() => registerForEvent(event.id)}
                          >
                            {isEventFull(event) ? 'Мест нет' : 'Зарегистрироваться'}
                          </Button>
                        )}
                      </>
                    )}
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

export default Events; 