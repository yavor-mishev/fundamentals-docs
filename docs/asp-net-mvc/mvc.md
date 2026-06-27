# MVC (Model-View-Controller)

MVC is an architecrural patternt for implementing user interfaces. It was originaly developed for desktop applications, but has since been adapted for web applications as well. Since the adoption of the pattern in web development many frameworks that have been created have enforced this pattern: ASP.NET MVC is one of them. Other similar MVC frameworks are **Ruby on Rails**, **Express for Node**.

**Model:** represents the application data and behavior in terms of the problem domain. it is independent of the UI. For a movie rental app this would mean that classes like Movie, Customer, Rental anmd Transaction would be part of the model. they do not rely on UI and so can be reused in different types of applications: desktop, mobile, ect. They are plain old CLR objects (POCOs) that contain properties and methods to manage the data and business logic.
**View:** the HTML markup that we display to the user. It is responsible for rendering the user interface and presenting the data from the model to the user.
**Controller:** responsible for handleing HTTP requests

Exapmle:
- our app is hosted on vidly.com
- we send a request to http://vidly.com/movies
- a controller will be selected to handle this request. This controller will get all the movied from the model, put them in a view and return the view to the client\\

**Router:** not part of the acronym but an important component of the MVC pattern. The selection of the controller which will have to handle a request is the responsibility of the router.

http://vidly.com/movies -> Router -> MoviesController