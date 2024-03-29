/*
Copyright 2007-2010 Selenium committers

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

package org.openqa.selenium.net;


/**
 * Provides information about the local network interfaces.
 * <p/>
 * Basically an abstraction created to allow stubbing of java.net.NetworkInterface, also soothes
 * some of the jdk1.2 idioms from this interface into jdk1.5 idioms.
 */
public interface NetworkInterfaceProvider {
  Iterable<NetworkInterface> getNetworkInterfaces();

  // TODO: Remove this whole method
  // This method should only return an iterface if it's named exactly "lo"
  NetworkInterface getLoInterface();
}
