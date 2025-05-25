import React, { useState, useEffect } from 'react';
import { Routes, Route, Navigate, Link } from 'react-router-dom';
import { Navbar, Nav, Container, Button } from 'react-bootstrap';
import Login from './pages/Login';
import Register from './pages/Register';
import Events from './pages/Events';
import EventForm from './pages/EventForm';
import Locations from './pages/Locations';
import LocationForm from './pages/LocationForm';
import Profile from './pages/Profile';
import './App.css';

function App() {
  const [user, setUser] = useState(null);

  useEffect(() => {
    const savedUser = localStorage.getItem('user');
    if (savedUser) {
      setUser(JSON.parse(savedUser));
    }
  }, []);

  const handleLogout = () => {
    localStorage.removeItem('user');
    setUser(null);
  };

  return (
    <div className="App">
      <Navbar bg="light" expand="lg" className="border-bottom">
        <Container>
          <Navbar.Brand as={Link} to="/" className="text-dark fw-bold">
            Мероприятия
          </Navbar.Brand>
          <Navbar.Toggle />
          <Navbar.Collapse className="justify-content-end">
            <Nav>
              {user ? (
                <>
                  <Nav.Link as={Link} to="/events" className="text-dark">
                    События
                  </Nav.Link>
                  <Nav.Link as={Link} to="/locations" className="text-dark">
                    Локации
                  </Nav.Link>
                  <Nav.Link as={Link} to="/profile" className="text-dark">
                    Профиль
                  </Nav.Link>
                  <Button variant="outline-secondary" className="ms-2" onClick={handleLogout}>
                    Выйти
                  </Button>
                </>
              ) : (
                <>
                  <Nav.Link as={Link} to="/login" className="text-dark">
                    Войти
                  </Nav.Link>
                  <Nav.Link as={Link} to="/register" className="text-dark">
                    Регистрация
                  </Nav.Link>
                </>
              )}
            </Nav>
          </Navbar.Collapse>
        </Container>
      </Navbar>

      <Container className="mt-4">
        <Routes>
          <Route path="/login" element={<Login setUser={setUser} />} />
          <Route path="/register" element={<Register setUser={setUser} />} />
          <Route path="/events" element={user ? <Events user={user} /> : <Navigate to="/login" />} />
          <Route path="/events/new" element={user ? <EventForm user={user} /> : <Navigate to="/login" />} />
          <Route path="/events/edit/:id" element={user ? <EventForm user={user} /> : <Navigate to="/login" />} />
          <Route path="/locations" element={user ? <Locations user={user} /> : <Navigate to="/login" />} />
          <Route path="/locations/new" element={user ? <LocationForm user={user} /> : <Navigate to="/login" />} />
          <Route path="/locations/edit/:id" element={user ? <LocationForm user={user} /> : <Navigate to="/login" />} />
          <Route path="/profile" element={user ? <Profile user={user} setUser={setUser} /> : <Navigate to="/login" />} />
          <Route path="/" element={user ? <Navigate to="/events" /> : <Navigate to="/login" />} />
        </Routes>
      </Container>
    </div>
  );
}

export default App;
