export class Event {
  constructor(data = {}) {
    this.id = data.id || null;
    this.title = data.title || '';
    this.description = data.description || '';
    this.date = data.date || '';
    this.time = data.time || '';
    this.maxParticipants = data.maxParticipants || 0;
    this.category = data.category || '';
    this.organizerId = data.organizerId || null;
    this.locationId = data.locationId || null;
    this.participants = data.participants || [];
  }

  validate() {
    const errors = [];
    if (!this.title.trim()) errors.push('Название обязательно');
    if (!this.description.trim()) errors.push('Описание обязательно');
    if (!this.date) errors.push('Дата обязательна');
    if (!this.time) errors.push('Время обязательно');
    if (this.maxParticipants <= 0) errors.push('Максимальное количество участников должно быть больше 0');
    if (!this.category.trim()) errors.push('Категория обязательна');
    if (!this.locationId) errors.push('Локация обязательна');
    return errors;
  }
} 