package ejercicio3.conPOyPFact;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

public class ProductComparisonPage {

    WebDriver driver;
    String myHandleId;
    String myHandleIdFROM;

    @FindBy(xpath = "//*[@id=\"top\"]/body/div/div[3]/button")
    WebElement closeButton;

    public ProductComparisonPage(WebDriver driver) {
        this.driver = driver;
    }

    public ShoesPage close() {
        closeButton.click();
        driver.switchTo().window(myHandleIdFROM);
        return PageFactory.initElements(driver, ShoesPage.class);
    }

    public String getProductsComparisonTitle() {
        return driver.getTitle();
    }
}
