package com.example.demo.services;

import com.example.demo.dto.*;
import com.lowagie.text.*;
import com.lowagie.text.pdf.PdfPCell;
import com.lowagie.text.pdf.PdfPTable;
import com.lowagie.text.pdf.PdfWriter;
import org.springframework.stereotype.Service;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.time.format.DateTimeFormatter;

@Service
public class PdfReportService {

    public byte[] generateSpendingReportPdf(SpendingReportDto report) throws DocumentException, IOException {
        Document document = new Document(PageSize.A4);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PdfWriter.getInstance(document, baos);

        document.open();

        // Заголовок отчета
        Font titleFont = new Font(Font.HELVETICA, 18, Font.BOLD);
        Paragraph title = new Paragraph("Отчет о тратах пользователей", titleFont);
        title.setAlignment(Element.ALIGN_CENTER);
        document.add(title);

        // Дата отчета
        Font dateFont = new Font(Font.HELVETICA, 12);
        Paragraph date = new Paragraph("Дата формирования: " + 
                report.getReportDate().format(DateTimeFormatter.ofPattern("dd.MM.yyyy HH:mm")), dateFont);
        date.setAlignment(Element.ALIGN_CENTER);
        document.add(date);
        document.add(new Paragraph(" "));

        // Общая сумма
        Font totalFont = new Font(Font.HELVETICA, 14, Font.BOLD);
        Paragraph grandTotal = new Paragraph("Общая сумма всех трат: " + report.getGrandTotal() + " руб.", totalFont);
        grandTotal.setAlignment(Element.ALIGN_CENTER);
        document.add(grandTotal);
        document.add(new Paragraph(" "));

        // Данные по пользователям
        for (UserSpendingReportDto userReport : report.getUserReports()) {
            addUserSection(document, userReport);
        }

        document.close();
        return baos.toByteArray();
    }
    
    public byte[] generateTopProductsReportPdf(TopProductsReportDto report) throws DocumentException, IOException {
        Document document = new Document(PageSize.A4);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PdfWriter.getInstance(document, baos);

        document.open();

        // Заголовок отчета
        Font titleFont = new Font(Font.HELVETICA, 18, Font.BOLD);
        Paragraph title = new Paragraph("Топ-10 самых продаваемых товаров", titleFont);
        title.setAlignment(Element.ALIGN_CENTER);
        document.add(title);

        // Дата отчета
        Font dateFont = new Font(Font.HELVETICA, 12);
        Paragraph date = new Paragraph("Дата формирования: " + 
                report.getReportDate().format(DateTimeFormatter.ofPattern("dd.MM.yyyy HH:mm")), dateFont);
        date.setAlignment(Element.ALIGN_CENTER);
        document.add(date);
        document.add(new Paragraph(" "));

        // Информация об анализе
        Font infoFont = new Font(Font.HELVETICA, 12);
        Paragraph info = new Paragraph("Всего товаров проанализировано: " + report.getTotalProductsAnalyzed(), infoFont);
        info.setAlignment(Element.ALIGN_CENTER);
        document.add(info);
        document.add(new Paragraph(" "));

        // Таблица топ товаров
        PdfPTable productsTable = new PdfPTable(5);
        productsTable.setWidthPercentage(100);
        productsTable.setWidths(new float[]{1, 3, 2, 2, 2});

        // Заголовки таблицы
        Font headerFont = new Font(Font.HELVETICA, 10, Font.BOLD);
        addTableHeader(productsTable, "Место", headerFont);
        addTableHeader(productsTable, "Название товара", headerFont);
        addTableHeader(productsTable, "Цена за ед.", headerFont);
        addTableHeader(productsTable, "Продано шт.", headerFont);
        addTableHeader(productsTable, "Общая выручка", headerFont);

        // Данные товаров
        Font cellFont = new Font(Font.HELVETICA, 10);
        int position = 1;
        for (ProductSalesReportDto product : report.getTopProducts()) {
            addTableCell(productsTable, String.valueOf(position), cellFont);
            addTableCell(productsTable, product.getProductName(), cellFont);
            addTableCell(productsTable, product.getUnitPrice() + " руб.", cellFont);
            addTableCell(productsTable, product.getTotalQuantitySold().toString(), cellFont);
            addTableCell(productsTable, product.getTotalRevenue() + " руб.", cellFont);
            position++;
        }

        document.add(productsTable);
        document.close();
        return baos.toByteArray();
    }

    private void addUserSection(Document document, UserSpendingReportDto userReport) throws DocumentException {
        // Заголовок пользователя
        Font userFont = new Font(Font.HELVETICA, 14, Font.BOLD);
        Paragraph userTitle = new Paragraph("Пользователь: " + userReport.getUsername() + 
                " (ID: " + userReport.getUserId() + ")", userFont);
        document.add(userTitle);

        // Общая сумма пользователя
        Font userTotalFont = new Font(Font.HELVETICA, 12, Font.BOLD);
        Paragraph userTotal = new Paragraph("Общая сумма трат: " + userReport.getTotalSpent() + " руб.", userTotalFont);
        document.add(userTotal);
        document.add(new Paragraph(" "));

        // Таблица заказов только если есть заказы
        if (!userReport.getOrders().isEmpty()) {
            PdfPTable ordersTable = new PdfPTable(3);
            ordersTable.setWidthPercentage(100);
            ordersTable.setWidths(new float[]{1, 2, 1});

            // Заголовки таблицы заказов
            Font headerFont = new Font(Font.HELVETICA, 10, Font.BOLD);
            addTableHeader(ordersTable, "ID заказа", headerFont);
            addTableHeader(ordersTable, "Статус", headerFont);
            addTableHeader(ordersTable, "Сумма заказа", headerFont);

            // Данные заказов
            Font cellFont = new Font(Font.HELVETICA, 10);
            for (OrderReportDto order : userReport.getOrders()) {
                addTableCell(ordersTable, order.getOrderId().toString(), cellFont);
                addTableCell(ordersTable, order.getOrderStatus(), cellFont);
                addTableCell(ordersTable, order.getTotalAmount() + " руб.", cellFont);
            }

            document.add(ordersTable);
        } else {
            // Если нет заказов, добавляем соответствующее сообщение
            Font noOrdersFont = new Font(Font.HELVETICA, 10, Font.ITALIC);
            Paragraph noOrders = new Paragraph("У пользователя нет заказов", noOrdersFont);
            document.add(noOrders);
        }
        
        document.add(new Paragraph(" "));
    }



    private void addTableHeader(PdfPTable table, String text, Font font) {
        PdfPCell cell = new PdfPCell(new Phrase(text, font));
        cell.setHorizontalAlignment(Element.ALIGN_CENTER);
        cell.setPadding(5);
        table.addCell(cell);
    }

    private void addTableCell(PdfPTable table, String text, Font font) {
        PdfPCell cell = new PdfPCell(new Phrase(text, font));
        cell.setHorizontalAlignment(Element.ALIGN_CENTER);
        cell.setPadding(3);
        table.addCell(cell);
    }
} 