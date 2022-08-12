package ejercicio3.conPOyPFact;

import org.openqa.selenium.Alert;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.util.Set;

public class ShoesPage {

    WebDriver driver;
    String myHandleId;

    @FindBy(css = ".products-grid > li:nth-child(5) > .product-info > .actions > ul > li:nth-child(2) > a")
    WebElement wingtipShoe;

    @FindBy(css = ".products-grid > li:nth-child(6) > .product-info > .actions > ul > li:nth-child(2) > a")
    WebElement suedeShoe;

    @FindBy(css = "button[title='Compare']")
    WebElement compareButton;

    @FindBy(linkText = "Clear All")
    WebElement clearAll;

    @FindBy(css = ".success-msg > ul > li > span")
    WebElement message;

    public ShoesPage(WebDriver driver) {
        this.driver = driver;
        //obtenemos el manejador de la ventana ShoesPage
        myHandleId = driver.getWindowHandle();
    }

    public void selectShoeToCompare(int number) {
        JavascriptExecutor jse = (JavascriptExecutor) driver;
        switch(number) {
            case 5: jse.executeScript("arguments[0].scrollIntoView();", wingtipShoe);
                wingtipShoe.click();
                break;
            case 6: jse.executeScript("arguments[0].scrollIntoView();", suedeShoe);
                suedeShoe.click();
                break;
        }
    }

    public ProductComparisonPage submitCompare() {
        //pulsamos sobre el botón para hacer la comparación
        compareButton.click(); //se abre una nueva ventana
        ProductComparisonPage comparisonPage = PageFactory.initElements(driver, ProductComparisonPage.class);

        //el handleID de la nueva ventana se añade al conjunto de manejadores del navegador
        Set<String> setIds = driver.getWindowHandles();
        String[] handleIds = setIds.toArray(new String[setIds.size()]);

        System.out.println("ID 0: " + handleIds[0]); //manejador de la ventana ShoesPage
        System.out.println("ID 1: " + handleIds[1]); //manejador de la venana ProductComparisonPage

        comparisonPage.myHandleIdFROM = handleIds[0];
        comparisonPage.myHandleId = handleIds[1];

        driver.switchTo().window(comparisonPage.myHandleId);
        return comparisonPage;
    }

    public String clearAll() {
        clearAll.click();
        Alert alert = driver.switchTo().alert();
        String message = alert.getText();
        alert.accept();
        return message;
    }

    public String getMessage() {
        return message.getText();
    }

    public String getShoesTitle() {
        return driver.getTitle();
    }
}
