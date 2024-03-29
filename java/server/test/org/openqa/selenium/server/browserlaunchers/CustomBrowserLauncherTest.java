/*
Copyright 2012 Selenium committers
Copyright 2012 Software Freedom Conservancy

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


package org.openqa.selenium.server.browserlaunchers;

import static org.junit.Assert.assertFalse;

import org.junit.Test;
import org.openqa.selenium.Capabilities;
import org.openqa.selenium.server.RemoteControlConfiguration;

public class CustomBrowserLauncherTest {

  @Test
  public void constructor_setsBrowserOptions() {
    Capabilities browserOptions = BrowserOptions.newBrowserOptions();
    RemoteControlConfiguration configuration = new RemoteControlConfiguration();
    CustomBrowserLauncher launcher =
        new CustomBrowserLauncher("command", "sessionId", configuration, browserOptions);

    Capabilities caps = launcher.browserConfigurationOptions;
    assertFalse(BrowserOptions.isSingleWindow(caps));
  }
}
