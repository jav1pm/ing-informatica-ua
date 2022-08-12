package ejercicio3.conPOyPFact;

import net.jodah.failsafe.internal.util.Assert;
import org.junit.jupiter.api.*;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.support.PageFactory;

import static org.junit.jupiter.api.Assertions.*;

class TestShoes {

    WebDriver driver;
    MyAccountPage accP;

    @BeforeAll
    static void setDriver() {
        System.setProperty("webdriver.chrome.driver",
                "./src/test/resources/drivers/chromedriver");
        Cookies.storeCookiesToFile("ejercicio1@test.com", "ejercicio1");
    }

    @BeforeEach
    public void setUp() {
        ChromeOptions chromeOptions = new ChromeOptions();

        // recuperamos el valor de la propiedad chromeHeadless definida en surefire
        boolean headless = Boolean.parseBoolean(System.getProperty("chromeHeadless"));

        // el método setHeadless() cambia la configuración de Chrome a modo headless
        chromeOptions.setHeadless(headless);

        // ahora creamos una instancia de CromeDriver a partir de chromeOptions
        driver = new ChromeDriver(chromeOptions);

        Cookies.loadCookiesFromFile(driver);

        driver.get("http://demo-store.seleniumacademy.com/customer/account/.");
        accP = PageFactory.initElements(driver, MyAccountPage.class);
    }

    @Test
    public void compareShoes() {
        // 1.
        Assertions.assertEquals("My Account", accP.getMyAccountTitle());

        // 2.
        ShoesPage shoesPage = accP.goShoesPage();

        // 3.
        Assertions.assertEquals("Shoes - Accessories", shoesPage.getShoesTitle());

        // 4.
        shoesPage.selectShoeToCompare(5);
        shoesPage.selectShoeToCompare(6);

        // 5.
        ProductComparisonPage comparisonPage = shoesPage.submitCompare();

        // 6.
        Assertions.assertEquals("Products Comparison List - Magento Commerce",
                comparisonPage.getProductsComparisonTitle());

        // 7.
        shoesPage = comparisonPage.close();

        // 8.
        Assertions.assertEquals("Shoes - Accessories", shoesPage.getShoesTitle());

        // 9.
        shoesPage.clearAll();

        // 10.
        Assertions.assertEquals("The comparison list was cleared.",
                shoesPage.getMessage());
    }

    @AfterEach
    public void tearDown() {
        driver.close();
    }
}