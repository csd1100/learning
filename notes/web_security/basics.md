# Web Security

## Cookies

- HTTP is stateless and Cookies are used to implement the session.
- They are used to keep track of authenticated user and for tracking
the user.
- RFC 6265 - Standard for Cookies. 
- Cookie is a HTTP header `Cookie: <key>=<value>`
- You can inspect cookies in `Application` tab in DevTools.
- Cookies have expiration dates.
- It can be done by `Expires=<timestamp>;` or `Max-Age=<time>;`.
- You can't delete a cookie. But we can set expiration date to something
in past so browser can clean it up.
- Attributes `Path=/route;`, `Domain=example.com;`.
- We can access cookie in DOM using `document.cookie`.
- Assigning new value to `document.cookie` will actually **append** to
the cookie.
- Using `httpOnly` will cookie make not accessible by Javascript in DOM.
- We can specify cookie only for HTTPS connection using `secure` attribute.
- Cookie can be signed by a private key and denoted by `signed` attribute.
- Use `samesite` to prevent cross-origin requests using the cookie.
- Using unique `sessionId` instead of user credentials is better way to handle sessions.
- When we use signed `sessionId` cookie we have unique cookie that cannot be modified
 at the client side by a script or bad actor.


## Injection Attacks

- SQL injection attacks: Adding SQL queries as inputs
- To avoid SQL injection attacks generally all SQL libraries have their own input /
query validation, use that. 
- Do **not** construct queries by string interpolation. Use string literal query with
arguments as parameters that will be validated by library or use prepared queries.
- Property injection attacks: Updating data directly by user input.
- **Always validate inputs. Only update data that should be updated. Do not directly
use / pass user input to functions.** 
- Use logs to check what input user might be providing so you can at least check
what happened when attack does happen.

## CSRF (Cross-Site Request Forgery)

- When user is authenticated, using that authenticated session to perform some action
that user does not intend or knows is CSRF attack.
- Bad actor makes you do perform something like credit card payment without you knowing.
- It is done by using existing cookie to make a request from browser without user knowing
like using hidden DOM elements.
- same site is not same as same origin.
- site is scheme,TLD-1,TLD i.e (`https://`www.`example.com`) where `https://`
is a scheme `example` is TLD-1 and TLD is `.com`.
- Origin is scheme,domain,port (`https://www.example.com:443`).
- Request can be from SameSite but have different origin.
- Cookies Samesite attribute can be `None`,`Lax`,`Strict`
- `None` always send the cookie.
- `Lax` allows cookies to be sent with top-level navigations and if request method
is safe (`GET`, `HEAD`).
- Top-level navigation means change in URL in bar.
- `Strict` only include cookie if request is sent from same site.
- To prevent:
    - Generating unique token to validate the request.
        - Do not include CSRF tokens with GET.
    - Use SameSite coookies.
    - Setup CORS policy to disallow unauthorized domains.
    - Referer based validation, not effective.


## Cross-Origin Resource Sharing (CORS)

- Security feature implemented by browsers to restrict web pages from making requests
to domain different than the one that served the page.
- `CORS` is **not** `CSRF` prevention mechanism. As,
- `POST` requests from **forms** are **not** covered CORS.
- Simple requests are **not** subject to `CORS`.
- Forms are simple request.
- `Content-Type: application/json` are not simple requests.
