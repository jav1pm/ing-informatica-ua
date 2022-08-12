package Ejercicio1.sinPageObject;

import org.junit.jupiter.api.*;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;

import java.time.Duration;

public class TestCreateAccount {

    private WebDriver driver;

    @BeforeAll
    static void setDriver() {
        System.setProperty("webdriver.chrome.driver",
                "./src/test/resources/drivers/chromedriver");
    }

    @BeforeEach
    public void setUp() {
        driver = new ChromeDriver();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));
        driver.get("http://demo-store.seleniumacademy.com/");
    }

    @Tag("OnlyOnce")
    @Test
    public void createAccount() {
        // 1. Verificar título de la página de inicio
        Assertions.assertEquals("Madison Island", driver.getTitle());

        // 2. Seleccionar Account e hiperenlance Login
        driver.findElement(By.xpath("//*[@id=\"header\"]/div/div[2]/div/a")).click();
        driver.findElement(By.linkText("Log In")).click();

        // 3. Verificar título de la página "Customer Login"
        Assertions.assertEquals("Customer Login", driver.getTitle());

        // 4. Seleccionar boton "Create Account"
        driver.findElement(By.cssSelector("a[title='Create an Account']")).click();

        // 5. Verificar título "Create new Costumer Account"
        Assertions.assertEquals("Create New Customer Account", driver.getTitle());

        // 6. Rellenar campos cuenta excepto "Confirmation"
        driver.findElement(By.name("firstname")).sendKeys("ejercicio1");
        driver.findElement(By.name("middlename")).sendKeys("ejercicio1");
        driver.findElement(By.cssSelector("input[name='lastname']")).sendKeys("ejercicio1");
        driver.findElement(By.cssSelector("input#email_address")).sendKeys("ejercicio1@test.com");
        driver.findElement(By.cssSelector("input[name='password']")).sendKeys("ejercicio1");
        driver.findElement(By.cssSelector("form#form-validate")).submit();

        // 7. Verificar mensaje "This is a required field"
        Assertions.assertEquals("This is a required field.",
                driver.findElement(By.cssSelector("div#advice-required-entry-confirmation")).getText());

        // 8. Rellenar campo que falta y volver a enviar el formulario
        driver.findElement(By.name("confirmation")).sendKeys("ejercicio1");
        driver.findElement(By.cssSelector("form#form-validate")).submit();

        // 9. Verificar título "My Account"
        Assertions.assertEquals("My Account", driver.getTitle());
    }

    @AfterEach
    public void tearDown() {
        driver.close();
    }
}
