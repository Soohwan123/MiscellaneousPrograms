$(function () {
    // Go to the server, get our list of employees

    // build the employee list add feature

    // When they do click the list, we have to figure our if it's going to be an Add or Update

    // Setup the modal for an add, or setup the modal for and update

    // They've git the action button

    $("#actionbutton").prop('disabled', false);
    $("#actionbutton").prop('disabled', true);

    document.addEventListener("keyup", e => {
        $("#modalstatus").removeClass(); //remove any existing css on div
        if ($("#StudentModalForm").valid()) {
            $("#modalstatus").attr("class", "badge bg-success"); //green
            $("#modalstatus").text("data entered is valid");
        }
        else {
            $("#modalstatus").attr("class", "badge bg-danger"); //red
            $("#modalstatus").text("fix errors");
        }
    });
    $("#StudentModalForm").validate({
        rules: {
            TextBoxTitle: { maxlength: 4, required: true, validTitle: true },
            TextBoxFirstname: { maxlength: 25, required: true },
            TextBoxLastname: { maxlength: 25, required: true },
            TextBoxEmail: { maxlength: 40, required: true, email: true },
            TextBoxPhone: { maxlength: 15, required: true },
        },
        errorElement: "div",
        messages: {
            TextBoxTitle: {
                required: "required 1-4 chars.", maxlength: "required 1-4 chars.", validTitle: "Mr. Ms. Mrs. or Dr."
            },
            TextBoxFirstname: {
                required: "required 1-25 chars.", maxlength: "required 1-25 chars."
            },
            TextBoxLastname: {
                required: "required 1-25 chars.", maxlength: "required 1-25 chars."
            },
            TextBoxPhone: {
                required: "required 1-15 chars.", maxlength: "required 1-15 chars."
            },
            TextBoxEmail: {
                required: "required 1-40 chars.", maxlength: "required 1-40 chars.", email: "need valid email format"
            }
        }
    });//StudentModalFrom.validate

    $.validator.addMethod("validTitle", (value) => { //custom rule
        return (value === "Mr." || value === "Ms." || value === "Mrs." || value === "Dr.");
    }, ""); //.validator.addMethod

    const getAll = async (msg) => {
        try {
            $("#employeeList").text("Finding Employee Information...");
            let response = await fetch(`/api/employee`);
            if (response.ok) {
                let payload = await response.json(); //this returns a promise, so we await it
                buildEmployeeList(payload);
                msg === "" ? // are we appending to an existing message
                    $("#status").text("Employees Loaded") : $("#status").text(`${msg} - Employees Loaded`)
            } else if (response.status !== 404) { //probably some other client side error
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            } else {  // else 404 not found
                $("#status").text(error.message);
            } // else
        } catch (error) {
            $("status").text(error.message);
        }
    }; //getAll

    const setupForUpdate = (id, data) => {
        $("#actionbutton").val("update");
        $("#modaltitle").html("<h4>update employee</h4>");
        $("#deletebutton").show();

        clearModalFields();
        data.map(employee => {
            if (employee.id === parseInt(id)) {
                //set value of ddl for departments
                $('#ddlDepartments').val(employee.departmentID);

                $("#TextBoxTitle").val(employee.title);
                $("#TextBoxFirstname").val(employee.firstname);
                $("#TextBoxLastname").val(employee.lastname);
                $("#TextBoxPhone").val(employee.phoneno);
                $("#TextBoxEmail").val(employee.email);
                sessionStorage.setItem("id", employee.id);
                sessionStorage.setItem("departmentId", employee.departmentID);
                sessionStorage.setItem("timer", employee.timer);
                $("#modalstatus").text("update data");
                $("#myModal").modal("toggle");
                $("#myModalLabel").text("Update");
            }// if
        });//data.map
    };//setupForUpdate

    const setupForAdd = () => {
        $("#actionbutton").val("add");
        $("#modaltitle").html("<h4>add employee</h4>")
        $("#myModal").modal("toggle");
        $("#modalstatus").text("add new employee");
        $("#myModalLabel").text("Add");
        $('#ddlDepartments').val(-1);
        $("#deletebutton").hide();
        clearModalFields();

    }; //setupForAdd


    const clearModalFields = () => {
        $("#TextBoxTitle").val("");
        $("#TextBoxFirstname").val("");
        $("#TextBoxLastname").val("");
        $("#TextBoxPhone").val("");
        $("#TextBoxEmail").val("");
        $('#ddlDepartments').val(-1);
        sessionStorage.removeItem("id");
        sessionStorage.removeItem("departmentId");
        sessionStorage.removeItem("timer");
        $("#myModal").modal("toggle");
        $("#EmployeeModalForm").validate().resetForm();
    };//clearModalFields



    const add = async () => {
        try {
            emp = new Object();
            emp.title = $("#TextBoxTitle").val();
            emp.firstname = $("#TextBoxFirstname").val();
            emp.lastname = $("#TextBoxLastname").val();
            emp.phoneno = $("#TextBoxPhone").val();
            emp.email = $("#TextBoxEmail").val();
            emp.departmentID = parseInt($("#ddlDepartments").val());
            emp.id = 4213;

            //send the employee info to the server ansychronously using POST
            let response = await fetch('/api/employee', {
                method: "POST",  // Post is for a new data, Put is for updating existing data
                headers: { 'Content-Type': 'application/json; charset=utf-8' },
                body: JSON.stringify(emp)
            });
            if (response.ok) //or check for response.status
            {
                let data = await response.json();
                getAll(data.msg);
            } else if (response.status !== 404) { //probably some other client side error
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            } else { // else 404 not found
                $("#status").text("no such path on server");
            } //else
        } catch (error) {
            $("#status").text(error.message);
        } // try/catch
        $("#myModal").modal("toggle");
    };//add

    const update = async () => {
        try {
            //go get the "current" employee data from session storage
            //set up a new client side instance of employee
            emp = new Object();

            //populate the properties
            //Overwrite with the updated values
            emp.title = $("#TextBoxTitle").val();
            emp.firstname = $("#TextBoxFirstname").val();
            emp.lastname = $("#TextBoxLastname").val();
            emp.phoneno = $("#TextBoxPhone").val();
            emp.email = $("#TextBoxEmail").val();
            emp.name = "";
            emp.picture64 = "";

            //stored earlier, numbers needed for Ids or http 401
            emp.id = parseInt(sessionStorage.getItem("id"));
            emp.departmentID = parseInt($("#ddlDepartments").val());
            emp.timer = sessionStorage.getItem("timer");
            emp.picture64 = null;

            //don't have to do ID, Timer, and department Id because they're already stored in employeeObject from before
            //sent the updated back to the server asynchronously using PUT
            let response = await fetch('/api/employee', {
                method: "PUT",
                headers: { 'Content-Type': 'application/json; charset=utf-8' },
                body: JSON.stringify(emp)
            });
            if (response.ok) //or check for response.status
            {
                let responseDate = await response.json();
                $("#status").text(responseDate.msg);
                getAll(data.msg); // very important !! timer will change. so if we wanna update twice in a row it will fail. so call getAll again for this!!

            } else if (response.status !== 404) { //probably some other client side error
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            } else { // else 404 not found
                $("#status").text("no such path on server");
            } //else
        } catch (error) {
            $("#status").text(error.message);
            console.table(error);
        }
    }; // update






    $("#actionbutton").mouseup(async (e) => {
        $("#actionbutton").val() === "Update" ? update() : add();
    });

    //finds the employee id out of the html element that is clicked
    $("#employeeList").click((e) => {
        clearModalFields();
        if (!e) e = window.event;
        let id = e.target.parentNode.id;
        if (id === "employeeList" || id === "") {
            id = e.target.id;
        } // clicked on row somewhere else

        if (id !== "status" && id !== "heading") {
            let data = JSON.parse(sessionStorage.getItem("allemployees"));
            id === "0" ? setupForAdd() : setupForUpdate(id, data);
        } //if
        else {
            return false; // ignore if they clicked on heading or status
        }
    }); //EmployeeList Click


    const buildEmployeeList = (data) => {
        $("#employeeList").empty();  //empty the list first
        div = $(`<div class="list-group-item text-white bg-secondary row d-flex" id="status">Employee Info</div>
        <div class= "list-group-item row d-flex text-center" id="heading">
            <div class="col-4 h4">Title</div>
            <div class="col-4 h4">First</div>
            <div class="col-4 h4">Last</div>
        </div>`);
        div.appendTo($("#employeeList"));
        sessionStorage.setItem("allemployees", JSON.stringify(data));
        btn = $(`<button class="list-group-item row d-flex text-center" id="0">...click to add employee</button>`)
        btn.appendTo($("#employeeList"));
        data.map(emp => {
            btn = $(`<button class="list-group-item row d-flex" id="${emp.id}">`);
            btn.html(`<div class="col-4" id="employeetitle${emp.id}">${emp.title}</div>
            <div class="col-4" id="employeefname${emp.id}">${emp.firstname}</div>
            <div class="col-4" id="employeelastname${emp.id}">${emp.lastname}</div>`
            );
            btn.appendTo($("#employeeList"));
        }); // map
    }; //buildEmployeeList

    const _delete = async () => {
        try {
            let response = await fetch(`/api/employee/${sessionStorage.getItem('id')}`, {
                method: 'DELETE',
                headers: { 'Content-Type': 'application/json; charset=utf-8' }
            });
            if (response.ok) //or check for response.status
            {
                let data = await response.json();
                getAll(data.msg);
            } else {
                $('#status').text(`Status - ${response.status}, Problem on delete server side, see server console`);
            } //else
            $('#myModal').modal('toggle');
        } catch (error) {
            $('#status').text(error.message);
        }
    }; // delete

    $('#deletebutton').click(() => {
        if (window.confirm('Are you sure')) {
            _delete();
        }
    })

    let loadDepartmentDDL = async () => {
        //go get all the department data
        response = await fetch(`/api/department`)
        if (!response.ok)
            throw new Error(`Status - ${response.status}, Text - ${response.statusText}`);
        let divs = await response.json();

        html = '';
        $('#ddlDepartments').empty();
        divs.map(div =>
            html += `<option value="${div.id}">${div.name}</option>`
        );
        $('#ddlDepartments').append(html);
    }

    getAll(""); //first grab the data from the server
    loadDepartmentDDL(); //calling departments
}); // jQuery method

// server was reached but server had a problem with the call
const errorRtn = (problemJson, status) => {
    if (status > 499) {
        $("status").text("Problem sever side, see debug console");
    } else {
        let keys = Object.keys(problemJson.errors)
        problem = {
            status: status,
            statusText: problemJson.errors[keys[0]][0], //first error
        };
        $("#status").text("Problem client side, see browser console");
        console.log(problem);
    }
}