export class User {
  constructor(data = {}) {
    this.id = data.id || null;
    this.email = data.email || '';
    this.password = data.password || '';
    this.name = data.name || '';
    this.phone = data.phone || '';
    this.bio = data.bio || '';
    this.role = data.role || 'participant'; // participant, organizer
    this.registeredEvents = data.registeredEvents || [];
    this.organizedEvents = data.organizedEvents || [];
  }

  validate() {
    const errors = [];
    if (!this.email.trim()) errors.push('Email обязателен');
    if (!this.email.includes('@')) errors.push('Некорректный email');
    if (!this.password || this.password.length < 6) errors.push('Пароль должен содержать минимум 6 символов');
    if (!this.name.trim()) errors.push('Имя обязательно');
    return errors;
  }
} 