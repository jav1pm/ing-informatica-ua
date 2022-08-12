package Ejercicio1.sinPageObject;

import org.junit.jupiter.api.*;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;

import java.time.Duration;

public class TestLogin {

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

    @Test
    public void loginOK() {
        // 1. Verificar título de la página de inicio
        Assertions.assertEquals("Madison Island", driver.getTitle());

        // 2. Seleccionar Account e hiperenlance Login
        driver.findElement(By.xpath("//*[@id=\"header\"]/div/div[2]/div/a")).click();
        driver.findElement(By.linkText("Log In")).click();

        // 3. Verificar título de la página "Customer Login"
        Assertions.assertEquals("Customer Login", driver.getTitle());

        // 4. Rellenar login y enviar formulario
        driver.findElement(By.cssSelector("input#email")).sendKeys("ejercicio1@test.com");
        driver.findElement(By.cssSelector("button#send2")).click();

        // 5. Verificar mensaje "This is a required field"
        Assertions.assertEquals("This is a required field.",
                driver.findElement(By.cssSelector("div#advice-required-entry-pass")).getText());

        // 6. Rellenamos el campo contraseña y volvemos a enviar el form
        driver.findElement(By.cssSelector("input#pass")).sendKeys("ejercicio1");
        driver.findElement(By.cssSelector("button#send2")).click();

        // 7. Verificar login con título "My Account"
        Assertions.assertEquals("My Account", driver.getTitle());
    }

    @Test
    public void loginFailed() {
        // 1. Verificar título de la página de inicio
        Assertions.assertEquals("Madison Island", driver.getTitle());

        // 2. Seleccionar Account e hiperenlance Login
        driver.findElement(By.xpath("//*[@id=\"header\"]/div/div[2]/div/a")).click();
        driver.findElement(By.linkText("Log In")).click();

        // 3. Verificar título de la página "Customer Login"
        Assertions.assertEquals("Customer Login", driver.getTitle());

        // 4. Rellenar login con password incorrecto
        driver.findElement(By.cssSelector("input#email")).sendKeys("ejercicio1@test.com");
        driver.findElement(By.cssSelector("input#pass")).sendKeys("incorrecto");
        driver.findElement(By.cssSelector("button#send2")).click();

        // 5. Verificar mensaje "Invalid login or password"
        Assertions.assertEquals("Invalid login or password.",
                driver.findElement(By.className("error-msg")).getText());
    }

    @AfterEach
    public void tearDown() {
        driver.close();
    }
}
