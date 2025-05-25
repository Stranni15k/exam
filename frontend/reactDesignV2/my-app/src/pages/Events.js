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
        <Button as={Link} to="/events/new" variant="success">
          Создать событие
        </Button>
      </div>

      <div className="mb-4">
        <ButtonGroup>
          <Button
            variant={filter === 'all' ? 'success' : 'outline-success'}
            onClick={() => setFilter('all')}
          >
            Все события
          </Button>
          <Button
            variant={filter === 'my' ? 'success' : 'outline-success'}
            onClick={() => setFilter('my')}
          >
            Мои события
          </Button>
          <Button
            variant={filter === 'registered' ? 'success' : 'outline-success'}
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
        <div>
          {filteredEvents.map(event => (
            <div key={event.id} className="event-list-item">
              <div className="event-header">
                <h3 className="event-title">{event.title}</h3>
                <span className="event-category">{event.category}</span>
              </div>
              
              <p className="text-muted mb-3">{event.description}</p>
              
              <div className="event-details">
                <div className="event-detail-item">
                  <strong>Дата:</strong>
                  <span>{event.date} в {event.time}</span>
                </div>
                <div className="event-detail-item">
                  <strong>Локация:</strong>
                  <span>{getLocationName(event.locationId)}</span>
                </div>
                <div className="event-detail-item">
                  <strong>Участники:</strong>
                  <span>{(event.participants || []).length} / {event.maxParticipants}</span>
                </div>
                <div className="event-detail-item">
                  <strong>Организатор:</strong>
                  <span>{event.organizerId === user.id.toString() ? 'Вы' : 'Другой'}</span>
                </div>
              </div>
              
              <div className="d-flex gap-2 mt-3">
                {event.organizerId === user.id.toString() ? (
                  <>
                    <Button as={Link} to={`/events/edit/${event.id}`} variant="outline-success" size="sm">
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
                        variant="success" 
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
            </div>
          ))}
        </div>
      )}
    </Container>
  );
};

export default Events; 