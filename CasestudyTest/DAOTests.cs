using System;
using Xunit;
using HelpdeskDAL;
using System.Diagnostics;
using System.Collections.Generic;
using System.Threading.Tasks;
using Xunit.Abstractions;

namespace CasestudyTests
{
    public class DAOTests
    {
        private readonly ITestOutputHelper output;
        public DAOTests(ITestOutputHelper output)
        {
            this.output = output;
        }
        [Fact]
        public async Task Employee_GetByEmailTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            Employee selectedEmployee = await dao.GetbyEmail("bs@abc.com");
            Assert.NotNull(selectedEmployee);
        }
        [Fact]
        public async Task Employee_GetByIdTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            Employee selectedEmployee = await dao.GetById(2);
            Assert.NotNull(selectedEmployee);
        }

        [Fact]
        public async Task Employee_GetAllTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            List<Employee> allEmployees = await dao.GetAll();
            Assert.NotNull(allEmployees);
        }

        [Fact]
        public async Task Employee_AddTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Employee newEmployees = new Employee();
            newEmployees.FirstName = "Soohwan";
            newEmployees.LastName = "Kim";
            newEmployees.PhoneNo = "(555)555-12343";
            newEmployees.Title = "Mr.";
            newEmployees.DepartmentId = 500;
            newEmployees.Email = "sc@sc.com";
            await dao.Add(newEmployees);
            Assert.True(newEmployees.Id > 0);
        }

        [Fact]
        public async Task Employee_UpdateTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Employee employeeForUpdate = await dao.GetById(1);
            if (employeeForUpdate != null)
            {
                string oldPhoneNo = employeeForUpdate.PhoneNo;
                string newPhoneNo = oldPhoneNo == "(555) 555-5551" ? "555-555-5555" : "(555) 555-5551";
                employeeForUpdate.PhoneNo = newPhoneNo;
            }
            Assert.True(await dao.Update(employeeForUpdate) == UpdateStatus.Ok);
        }

        [Fact]
        public async Task Employee_DeleteTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Assert.True(await dao.Delete(8) == 1);
        }

        [Fact]
        public async Task Employee_ConcurrencyTest()
        {
            EmployeeDAO dao1 = new EmployeeDAO();
            EmployeeDAO dao2 = new EmployeeDAO();
            Employee employeeForUpdate1 = await dao1.GetById(1);
            Employee employeeForUpdate2 = await dao2.GetById(1);

            if (employeeForUpdate1 != null)
            {
                string oldPhoneNo = employeeForUpdate1.PhoneNo;
                string newPhoneNo = oldPhoneNo == "(555)555-1234" ? "555-555-5555" : "(555)555-1234";
                employeeForUpdate1.PhoneNo = newPhoneNo;
                if (await dao1.Update(employeeForUpdate1) == UpdateStatus.Ok)
                {
                    //need to change the phone # to something else
                    employeeForUpdate2.PhoneNo = "666-666-6666";
                    Assert.True(await dao2.Update(employeeForUpdate2) == UpdateStatus.Stale);
                }
                else
                    Assert.True(false);
            }
        }
        [Fact]
        public async Task Employee_LoadPicsTest()
        {
            try
            {
                DALUtil util = new DALUtil();
                Assert.True(await util.AddEmployeePicsToDb());

            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
        }

        [Fact]
        public async Task Call_ComprehensiveTest()
        {
            CallDAO cdao = new CallDAO();
            EmployeeDAO edao = new EmployeeDAO();
            ProblemDAO pdao = new ProblemDAO();

            Employee Kim = await edao.GetbyEmail("sc@sc.com");
            Employee burnur = await edao.GetbyEmail("bs@abc.com");
            Problem badDrive = await pdao.GetByDescription("Hard Drive Failure");

            Call call = new Call
            {
                DateOpened = DateTime.Now,
                DateClosed = null,
                OpenStatus = true,
                EmployeeId = Kim.Id,
                TechId = burnur.Id,
                ProblemId = badDrive.Id,
                Notes = "Kim's drive is shot, Burner to fix it"
            };

            int newCallId = await cdao.Add(call);
            output.WriteLine("New Call Generated - Id = " + newCallId);
            call = await cdao.GetById(newCallId);
            byte[] oldtimer = call.Timer;
            output.WriteLine("New Call Retrieved");
            call.Notes += "\n Ordered new drive!";

            if(await cdao .Update(call) == UpdateStatus.Ok)
            {
                output.WriteLine("Call was updated " + call.Notes);
            }
            else
            {
                output.WriteLine("Call was not updated!");
            }

            call.Timer = oldtimer;
            call.Notes = "doesn't matter data is stale now";
            if(await cdao .Update(call) == UpdateStatus.Stale)
            {
                output.WriteLine("Call was not updated due to stale data");
            }
            cdao = new CallDAO();
            call = await cdao.GetById(newCallId);
            if(await cdao .Delete(newCallId) == 1)
            {
                output.WriteLine("Call was deleted!");
            }
            else
            {
                output.WriteLine("Call was not deleted");
            }
            Assert.Null(await cdao.GetById(newCallId));
        }
    }

}