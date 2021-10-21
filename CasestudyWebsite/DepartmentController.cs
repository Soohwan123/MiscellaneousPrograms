using HelpdeskViewModels;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;


namespace CasestudyWebsite.Controllers
{
    [Route("api/Department")]             //Important!!
    [ApiController]
    public class DepartmentController : Controller
    {
        [HttpGet]
        public async Task<IActionResult> GetAll()
        {
            try
            {
                DepartmentViewModel viewModel = new DepartmentViewModel();
                List<DepartmentViewModel> allDepartments = await viewModel.GetAll();
                return Ok(allDepartments);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError); //something went wrong
            }
        }
    }
}
