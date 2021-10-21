$(function () {

    $("#getButton").click(async (e) => {
        try {
            let email = $("#TextBoxEmail").val();
            $("#status").text("please wait...");
            let response = await fetch(`/api/employee/${email}`);
            if (response.ok)
            {
                let data = await response.json(); //this returns a promise, so we await it
                if (data.email !== "not found")
                {
                    $("#lastname").text(data.lastname);
                    $("#title").text(data.title);
                    $("#firstname").text(data.firstname); // we all know in StudentViewModel is Firstname, Title etc... but in js all things down to lower-case
                    $("#phone").text(data.phoneno);
                    $("#status").text("employee found");
                } else
                {
                    $("firstname").text("not found");
                    $("#lastname").text("");
                    $("#title").text("");
                    $("#phone").text("");
                    $("#status").text("no such employee");
                }
            } else if (response.status !== 404)
            {
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            } else
            { //else 404 not found
                $("#status").text("no such path on server")
            }
        } catch (error) { //catastrophic
            $("#status").text(error.message);
        }
    });

    $("#hub").click(async (e) => {
        try {
            clearModalFields();
            $("#status").text("please wait...");
            $("#myModal").modal("toggle");
        } catch (error) { //catastrophic
            $("#status").text(error.message);
        }
    });

    const clearModalFields = () => {
        $("#title").val("");
        $("#firstname").val("");
        $("#lastname").val("");
        $("#phone").val("");
        $("#TextBoxEmail").val("");
  
    };//clearModalFields

    $("#actionbutton").mouseup(async (e) => {
        $("#actionbutton").val() === "Update" ? update() : add();
    });



});

// server was reached but server had a problem with the call
const errorRtn = (problemJson, status) => {
    if (status > 499)
    {
        $("status").text("Problem sever side, see debug console");
    } else
    {
        let keys = Object.keys(problemJson.errors)
        problem = {
            status: status,
            statusText: problemJson.errors[keys[0]][0], //first error
        };
        $("#status").text("Problem client side, see browser console");
        console.log(problem);
    }
}