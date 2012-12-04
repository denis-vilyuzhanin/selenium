package org.openqa.selenium;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.testing.JUnit4TestBase;
import org.openqa.selenium.testing.SeleniumTestRunner;

import static org.junit.Assert.assertEquals;

@RunWith(SeleniumTestRunner.class)
public class SendsEchoTest extends JUnit4TestBase {

	@Test
	public void echo() {
		final String MESSAGE = "Hello";
		String echoMessage = ((SendsEcho)driver).echo(MESSAGE);
		assertEquals(MESSAGE, echoMessage);
	}
}
