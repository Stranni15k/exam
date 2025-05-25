export class Location {
  constructor(data = {}) {
    this.id = data.id || null;
    this.name = data.name || '';
    this.address = data.address || '';
    this.description = data.description || '';
    this.capacity = data.capacity || 0;
    this.amenities = data.amenities || []; // парковка, проектор, доступ для колясок
  }

  validate() {
    const errors = [];
    if (!this.name.trim()) errors.push('Название локации обязательно');
    if (!this.address.trim()) errors.push('Адрес обязателен');
    if (this.capacity <= 0) errors.push('Вместимость должна быть больше 0');
    return errors;
  }
} 