using HelpdeskViewModels;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace CasestudyWebsite.Controllers
{
    [Route("api/employee")]
    [ApiController]
    public class EmployeeController : ControllerBase
    {
        //would have to hit this route
        //api/Student/Corcoran
        [HttpGet("{email}")]
        public async Task<IActionResult> GetByEmailAsync(string email)
        {
            try
            {
                EmployeeViewModel vm = new EmployeeViewModel();
                {
                    vm.Email = email;
                };
                await vm.GetByEmail();
                return Ok(vm);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError); //somethind went wrong
            }
        }
    }
}
