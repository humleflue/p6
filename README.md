# P6 - Support Vector Classifier On Low Consumption Devices

[![Test C Code (3 vectors)](https://github.com/humleflue/p6/actions/workflows/c-compile-old.yml/badge.svg)](https://github.com/humleflue/p6/actions/workflows/c-compile-old.yml)
[![Test C Code (23 vectors)](https://github.com/humleflue/p6/actions/workflows/c-compile-new.yml/badge.svg)](https://github.com/humleflue/p6/actions/workflows/c-compile-new.yml)
![Code Status](https://img.shields.io/static/v1?label=Code%20status&message=LGTM&color=brightgreen&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAEpklEQVRIx52VT4jdVxXHP+fc+7vv9zKZycskeZmp6bSTTFqoTanFYLHaLgQxUvFvwaLduOiq6EoQXEgXYkQE14Juumh1I25akCbZiuA/SgmJpf/SDJXJmMbMe+/3595zunhNQdpJgmd1OOfe++Hee875CrewH33rMf/u5zKSd7i8+S77xkOOrK3w65fg2ef+LLfav+uC7z/xqJ9YqXho/Sq//+N5/vGvGa6L7Oxkjq4Yj39hBKNP8u2fnr0pRH7x9Od9e5Y4/dwZAXjmm6f8sxvKg8eFzc1LvHzuAq9eLFzpAqUUcu90Enhg3PLIpyvywqP84DdndoXI1+/d5/ccP8zBg/tBh9R1x8Yh2LnyBhL28cr5wiuvbdJIxAVyLrSNEtsJ4wOJEyfv5scvnN8d8Pj6skMGKRz9xAFO3Hc3tV5iOoV//v0a2ztOZ0YIQhZFMIor03ZKM2u4c3U/d93/IKdfOCcAP/zaw/6Z+0eMlpZ44/XLyJfXx45HNM7oe2chOo+dPMzFV9/k8nQBUMBQmQOi9zhKzplBJbi1fOrh4xw5vMKxu8a8fO6vXLzwH/peaLMgp+4cO6p4aBCDEBIi7zGoapqsqAkKFBWSKSaGe8BLy7DuObY+ZmvrKlevZZoMKhUiETziXohOQdwQiwzEyDjvXBOa6RQkUCnsCcZoNKSuakrvNF3BRehnhY4hr7/9Fmm4TNGOUCIqShCf/8FTD2349vYWRmaYanqUduJ0RQmVoGIEESrpiRGmbWDa9phkwIlSo2SWFiNiLV4qrBjmYCHN++CpjWWf5YxWCdPA9o7Ttz2pclR9DlAhxELbC8UDLnleJn1FiLB3j+Ke8SJEcdbWVqA0RABJIB7JOIbTtFO6pkOyQoQYFR0omAORpm1xlOjg3hPTEHBEhcqd1bV1fnn2bwJ8ABBBBEyguCO0LO6NDEJAQyAERXAGKbHTRxaYgTvtLDOZdAzqBaAAkMX41QeHfwjYf3DZm80rYn1AMe4YLqI6L09zI3eZ96bQpAlb1yasjUegLYPFmr11orOWyJBcMnVKHz+Lnjh2yCclI03P0kI1v5GBW2HaZqY5AE42WBxACEaMCZHIzqywUEdiFfjdxXf/p6vjDSeEgPc9uCMiqApmRilO1MggQHZFxDEgyvz5VI1ighWjqH9kVHwIEKlIeUqolBD0RpAuO23vuDtWDCdRUKQKCAJ04BXFCnWsPwLQG87zFy7JgdWjHBrfQagqDEADFiNpmKhTxd7hkOHASFoQEVyFQMC94EDTdrsDAB75xlc4+aUv4nFesgVjkCIpBmJUEKiCEJNgocO0sGfPEpAZDhJ/eHNbbktwvvPAEe+aCe6CG7gL5hkrRiUBxykhU1UD1ldX2fr3dX52+ue2+tUnw20BfvK9J7u/nH2xigheCoaSYiAoTLp5vWMdKsKL70xvqmj6ccFnf/t8Gi0foS2BSQ9thlkR+iL05rR9T1sKG/fd+6f/W5NPbayV3E70+mwKLqSQCCEwyQW3lqVBxZnN/95S9HW3xEuvvR3cMhEIIvQITTEcBU14DtyO6c2SUbk+WhgQg4G0qPYkZtShoFFvC/A+fN4nxfWZo4AAAAAASUVORK5CYII=)

Our bachelor's project on Software at Aalborg University.

## Development Setup Guide
To be able to run the code in the `simplicity-studio` directory, you will have to:
1. clone this repo into the `C:\GitRepos` directory.
2. Open Simplicity studio then click Files -> Switch Workspace then select the simplicity-studio repo in the p6 directory and click Launch.
3. Click Files (again) -> import, browse and select the `./simplicity-studios/kinProject` directory. 
4. Click Next, Next, and name the project kinProject (remove the \_2).
5. In the project explorer click on `main.c` and now you can debug using F11 or Run -> Debug.

## FAQ
Q: Why do I **have to** clone into `C:\GitRepos`?
A: Because Simplicity Studio workspaces depend on absolute paths.
