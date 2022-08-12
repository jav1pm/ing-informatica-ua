package ejercicio2.conPO;

import org.junit.jupiter.api.*;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;

public class TestLogin2 {

    WebDriver driver;
    HomePage poHome;
    CustomerLoginPage poCustomerLogin;
    MyAccountPage poMyAccount;

    @BeforeAll
    static void setDriver() {
        System.setProperty("webdriver.chrome.driver",
                "./src/test/resources/drivers/chromedriver");
    }

    @BeforeEach
    public void setUp() {
        driver = new ChromeDriver();
        poHome = new HomePage(driver);
    }

    @Test
    public void test_Login_Correct() {
        Assertions.assertEquals("Madison Island", poHome.getHomePageTitle());
        poCustomerLogin = poHome.goLogin();
        Assertions.assertEquals("Customer Login", poCustomerLogin.getCustomerLoginTitle());
        poCustomerLogin.loginOK("ejercicio1@test.com", "ejercicio1");
        poMyAccount = new MyAccountPage(driver);
        Assertions.assertEquals("My Account", poMyAccount.getAccountTitle());
    }

    @Test
    public void test_Login_Incorrect() {
        Assertions.assertEquals("Madison Island", poHome.getHomePageTitle());
        poCustomerLogin = poHome.goLogin();
        Assertions.assertEquals("Customer Login", poCustomerLogin.getCustomerLoginTitle());
       Assertions.assertEquals("Invalid login or password.",
               poCustomerLogin.loginFailed("error@gmail.com", "incorrecto"));
    }

    @AfterEach
    public void tearDown() {
        driver.close();
    }
}
